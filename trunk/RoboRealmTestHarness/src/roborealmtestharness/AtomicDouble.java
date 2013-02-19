/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package roborealmtestharness;

/**
 *
 * @author rsaccone
 */
import static java.lang.Double.*;
import java.util.concurrent.atomic.AtomicLong;

class AtomicDouble extends Number {

    private AtomicLong bits;

    public AtomicDouble() {
        this(0d);
    }

    public AtomicDouble(double initialValue) {
        bits = new AtomicLong(doubleToLongBits(initialValue));
    }

    public final boolean compareAndSet(double expect, double update) {
        return bits.compareAndSet(doubleToLongBits(expect),
                                  doubleToLongBits(update));
    }

    public final void set(double newValue) {
        bits.set(doubleToLongBits(newValue));
    }

    public final double get() {
        return longBitsToDouble(bits.get());
    }

    public double doubleValue() {
        return get();
    }

    public final double getAndSet(double newValue) {
        return longBitsToDouble(bits.getAndSet(doubleToLongBits(newValue)));
    }

    public final boolean weakCompareAndSet(double expect, double update) {
        return bits.weakCompareAndSet(doubleToLongBits(expect),
                                      doubleToLongBits(update));
    }

    @Override
    public float floatValue() { 
        return (float) doubleValue(); 
    }
    
    @Override
    public int intValue() { 
        return (int) get();
    }
    
    @Override
    public long longValue() { 
        return (long) get();          
    }
}