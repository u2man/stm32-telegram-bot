/******************************************************************************
* Copyright (c) 2018(-2022) STMicroelectronics.
* All rights reserved.
*
* This file is part of the TouchGFX 4.20.0 distribution.
*
* This software is licensed under terms that can be found in the LICENSE file in
* the root directory of this software component.
* If no LICENSE file comes with this software, it is provided AS-IS.
*
*******************************************************************************/

/**
 * @file touchgfx/transitions/SlideTransition.hpp
 *
 * Declares the touchgfx::SlideTransition class.
 */
#ifndef TOUCHGFX_SLIDETRANSITION_HPP
#define TOUCHGFX_SLIDETRANSITION_HPP

#include <touchgfx/Drawable.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/hal/Types.hpp>
#include <touchgfx/transitions/Transition.hpp>
#include <touchgfx/widgets/SnapshotWidget.hpp>

namespace touchgfx
{
/**
 * A Transition that slides from one screen to the next. It does so by moving a SnapShotWidget
 * with a snapshot of the Screen transitioning away from, and by moving the contents of
 * Screen transitioning to.
 *
 * @see Transition
 */
template <Direction templateDirection>
class SlideTransition : public Transition
{
public:
    /**
     * Initializes a new instance of the SlideTransition class.
     *
     * @param  transitionSteps (Optional) Number of steps (ticks) in the transition animation, default is 20.
     */
    SlideTransition(const uint8_t transitionSteps = 20)
        : Transition(),
          snapshot(),
          snapshotPtr(&snapshot),
          handleTickCallback(this, &SlideTransition::tickMoveDrawable),
          animationSteps(transitionSteps),
          animationCounter(0),
          calculatedValue(0)
    {
        if (HAL::USE_ANIMATION_STORAGE)
        {
            snapshot.setPosition(0, 0, HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT);
            snapshot.makeSnapshot();

            switch (templateDirection)
            {
            case EAST:
                targetValue = -HAL::DISPLAY_WIDTH;
                break;
            case WEST:
                targetValue = HAL::DISPLAY_WIDTH;
                break;
            case NORTH:
                targetValue = HAL::DISPLAY_HEIGHT;
                break;
            case SOUTH:
                targetValue = -HAL::DISPLAY_HEIGHT;
                break;
            }
        }
    }

    /**
     * Handles the tick event when transitioning. It moves the contents of the Screen's
     * container and a SnapshotWidget with a snapshot of the previous Screen. The direction
     * of the transition determines the direction the contents of the container and the
     * SnapshotWidget moves.
     */
    virtual void handleTickEvent()
    {
        if (!HAL::USE_ANIMATION_STORAGE)
        {
            done = true;
            return;
        }

        Transition::handleTickEvent();

        // Calculate new position or stop animation
        animationCounter++;
        if (animationCounter <= animationSteps)
        {
            // Calculate value in [0;targetValue]
            calculatedValue = EasingEquations::cubicEaseOut(animationCounter, 0, targetValue, animationSteps);

            // Note: Result of "calculatedValue & 1" is compiler dependent for negative values of calculatedValue
            if (calculatedValue % 2)
            {
                // Optimization: calculatedValue is odd, add 1/-1 to move drawables modulo 32 bits in framebuffer
                calculatedValue += (calculatedValue > 0 ? 1 : -1);
            }
        }
        else
        {
            // Final step: stop the animation
            done = true;
            animationCounter = 0;
            return;
        }

        // Move snapshot
        switch (templateDirection)
        {
        case EAST:
        case WEST:
            // Convert to delta value relative to current X
            calculatedValue -= snapshot.getX();
            snapshot.moveRelative(calculatedValue, 0);
            break;
        case NORTH:
        case SOUTH:
            // Convert to delta value relative to current Y
            calculatedValue -= snapshot.getY();
            snapshot.moveRelative(0, calculatedValue);
            break;
        }

        // Move children with delta value for X or Y
        screenContainer->forEachChild(&handleTickCallback);
    }

    virtual void tearDown()
    {
        if (HAL::USE_ANIMATION_STORAGE && screenContainer)
        {
            screenContainer->remove(snapshot);
        }
    }

    virtual void init()
    {
        if (HAL::USE_ANIMATION_STORAGE)
        {
            Transition::init();

            Callback<SlideTransition, Drawable&> initCallback(this, &SlideTransition::initMoveDrawable);
            screenContainer->forEachChild(&initCallback);

            screenContainer->add(snapshot);
        }
    }

protected:
    /**
     * Moves the Drawable to its initial position, just outside the actual display.
     *
     * @param [in] d The Drawable to move.
     */
    virtual void initMoveDrawable(Drawable& d)
    {
        switch (templateDirection)
        {
        case EAST:
            d.moveRelative(HAL::DISPLAY_WIDTH, 0);
            break;
        case WEST:
            d.moveRelative(-HAL::DISPLAY_WIDTH, 0);
            break;
        case NORTH:
            d.moveRelative(0, -HAL::DISPLAY_HEIGHT);
            break;
        case SOUTH:
            d.moveRelative(0, HAL::DISPLAY_HEIGHT);
            break;
        default:
            // Nothing to do here
            break;
        }
    }

    /**
     * Moves the Drawable.
     *
     * @param [in] d The Drawable to move.
     */
    virtual void tickMoveDrawable(Drawable& d)
    {
        if (&d == snapshotPtr)
        {
            return;
        }

        switch (templateDirection)
        {
        case EAST:
        case WEST:
            d.moveRelative(calculatedValue, 0);
            break;
        case NORTH:
        case SOUTH:
            d.moveRelative(0, calculatedValue);
            break;
        }
    }

    SnapshotWidget snapshot;     ///< The SnapshotWidget that is moved when transitioning.
    SnapshotWidget* snapshotPtr; ///< Pointer pointing to the snapshot used in this transition.The snapshot pointer

private:
    Callback<SlideTransition, Drawable&> handleTickCallback; ///< Callback used for tickMoveDrawable().

    const uint8_t animationSteps; ///< Number of steps the transition should move per complete animation.
    uint8_t animationCounter;     ///< Current step in the transition animation.
    int16_t targetValue;          ///< The target value for the transition animation.
    int16_t calculatedValue;      ///< The calculated X or Y value for the snapshot and the children.
};

} // namespace touchgfx

#endif // TOUCHGFX_SLIDETRANSITION_HPP
