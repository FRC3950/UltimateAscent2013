/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package roborealmtestharness;

/**
 *
 * @author rsaccone
 */
public class RoboRealmVisionTargetFinder implements Runnable {
    
    public enum State
    {
        Stopped,
        Starting,
        Running,
        Error
    }
    
    private static final String ROBO_REALM_SERVER_ADDRESS = "10.39.50.9";
    
    private static final int NUM_BFR_COORDS = 8;
    private static final int MAX_SAMPLES = 30;                     // Number of samples to use in averaging the distance.
    private static final long SAMPLING_INTERVAL_IN_MS = 1 * 1000;  // How often to calculate the distance and target angle.
    
    private static final int RIGHTY_INDEX = 1;
    private static final int RIGHTYY_INDEX = 7;
    private static final int LEFTY_INDEX = 3;
    private static final int LEFTYY_INDEX = 5;
    
    private final Object lock = new Object();  // Lock used to syncrhonize changes to internal state.
    private State state;
    private Thread finderThread;
    private RR_API roboRealm;
    private ImageDataProcessor imgDataProcessor;
    private VisionTargetFinderCallback msgCallback = null;

    private GoalType goalType;
    private int numSamples = 0;
    private double distanceSum = 0.0;
    private AtomicDouble avgDistance = new AtomicDouble();
    private AtomicDouble targetAngle = new AtomicDouble();

    private volatile boolean quit = false;

    public RoboRealmVisionTargetFinder(GoalType targetToFind,
                                       VisionTargetFinderCallback msgCallback)
    {
        if (msgCallback != null) {
            this.msgCallback = msgCallback;
        }
        
        state = State.Stopped;
        goalType = targetToFind;
        roboRealm = new RR_API();
    }

    public void start()
    {
        synchronized(lock)
        {
            if (finderThread == null) {
                finderThread = new Thread(this);
                state = State.Starting;
                finderThread.start();
            }
        }
    }

    public void stop()
    {
        quit = true;
    }
    
    public State getState() {
        synchronized(lock) {
            return state;
        }
            
    }

    public double getTargetAngle() {
        return targetAngle.get();
    }
    
    public double getAvgDistance() {
        return avgDistance.get();
    }

    // Runnable interface method
    @SuppressWarnings("SleepWhileInLoop")
    @Override
    public void run() 
    {
        try {
            if (!roboRealm.connect(ROBO_REALM_SERVER_ADDRESS)) {
                 // To do handle the error.
                setState(State.Error);
                return;
            }

            int imageHeight = getImageHeight();

            if (imageHeight == 0) {
                // Couldn't get the image height. Handle the error.
                setState(State.Error);
                return;
            }

            imgDataProcessor = new ImageDataProcessor(goalType, imageHeight);
            
            setState(State.Running);

            while (!quit) {
                double currAvgDistance = calcAvgImageDistance();
                double angle = 0.0; // Start out with no angle.
                
                if (currAvgDistance > 0.0) {
                    angle = imgDataProcessor.calculateAngleFromDistance(currAvgDistance);

                }
                
                // Publish the angle for consumers.
                targetAngle.set(angle);
                
                // Publish the avg distance for consumers.
                avgDistance.set(currAvgDistance);
                
                // Notify any subscriber that wants callbacks
                if (msgCallback != null) {
                    msgCallback.calcResult(this, goalType, currAvgDistance, angle);
                }

                // Have the thread sleep so that it isn't 
                // consuming excessive CPU by calculating
                // the distance and angle too frequently.
                long timeToSleep = SAMPLING_INTERVAL_IN_MS;

                while (!quit && (timeToSleep > 0)) {
                    long startSleep = System.currentTimeMillis();

                    try {
                        Thread.sleep(timeToSleep);
                    }
                    catch (InterruptedException ex) {
                        // Something woke up the thread.
                    }
                    timeToSleep -= (System.currentTimeMillis() - startSleep);
                }
            }
            
            setState(State.Stopped);
        }
        catch (Exception ex) {
            setState(State.Error);
        }
    }
        
    private void setState(State newState) {
        synchronized(lock) {
            state = newState;
        }
    }

    private double calcAvgImageDistance()
    {
        double[] coords = getBfrCoords();

        if (coords != null) {
            // System.out.println("Bfr coords = " + Arrays.toString(coords));

            int numBlobs = coords.length / NUM_BFR_COORDS;

            for (int indexOffset = 0, blobNum = 0; blobNum < numBlobs; ++blobNum, indexOffset += NUM_BFR_COORDS) {
                distanceSum += imgDataProcessor.calculateDistance(coords[indexOffset + RIGHTY_INDEX], coords[indexOffset + RIGHTYY_INDEX], coords[indexOffset + LEFTY_INDEX], coords[indexOffset + LEFTYY_INDEX]);
                ++numSamples;
            }
        }
        else {
            ++numSamples;

            System.out.println("Couldn't get BFR_COORDINATES!");
        }

        double distance = distanceSum / numSamples;

        if (numSamples > MAX_SAMPLES) {
            System.out.println("Resetting sample count.");
            numSamples = 1;
            distanceSum = distance;
        }
        else if ((distance == Double.POSITIVE_INFINITY) || (distance == Double.NEGATIVE_INFINITY)) {
            distance = 0.0;
            numSamples = 0;
            distanceSum = 0;
        }

         return distance;
    }

    private double[] getBfrCoords()
    {
        double[] result = null;

        String response = roboRealm.getVariable("BFR_COORDINATES");

        if (response != null) {
            String[] strCoords = response.split(",");

            if ((strCoords != null) && (strCoords.length >= NUM_BFR_COORDS) && ((strCoords.length % NUM_BFR_COORDS) == 0)) {
                result = convertStringsToDoubles(strCoords);
            }
        }

        return result;
   }

    private static double[] convertStringsToDoubles(String[] strCoords)
    {
        double[] coords = new double[strCoords.length];

        for (int index = 0; index < strCoords.length; ++index) {
            coords[index] = Double.parseDouble(strCoords[index]);
        }

        return coords;
    }

    private int getImageHeight()
    {
       String response = roboRealm.getVariable("IMAGE_HEIGHT");

       if (response != null) {
            return Integer.parseInt(response);
       }

       return 0;
    }
}
