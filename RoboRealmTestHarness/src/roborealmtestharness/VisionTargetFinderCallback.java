/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package roborealmtestharness;

/**
 *
 * @author rsaccone
 */
public interface VisionTargetFinderCallback {
    
    // Called each time the vision target finder has calculated a result.
    void calcResult(RoboRealmVisionTargetFinder finder,
                    GoalType goalType,
                    double avgDistance,
                    double angle);
}
