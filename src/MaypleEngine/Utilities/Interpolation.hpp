/*!****************************************************************************
\file    Interpolation.hpp
\author  Jacob Nelson (jacob.nelson)
\date    Apr 21, 2015

\brief   Contains helpful interpolation functions used in animations.

\par     Checked By:

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/
#pragma once 

namespace animationSpace
{
  template <typename T, typename T2>
  void Linear(T * result, T start_value, T changeIn_value, 
                    T2 current_time, T2 duration)
  {
    *result = (current_time / duration) * changeIn_value + start_value;
  }

  template <typename T, typename T2>
  void SinosoidalIn(T * result, T start_value, T changeIn_value, 
                          T2 current_time, T2 duration)
  {
    *result = -changeIn_value * cos((current_time / duration) * 
              (PI / 2)) + changeIn_value + start_value;
  }

  template <typename T, typename T2>
  void SinosoidalOut(T * result, T start_value, T changeIn_value, 
                           T2 current_time, T2 duration)
  {
    *result = changeIn_value * sin(current_time / duration * 
              (PI / 2)) + start_value;
  }

  template <typename T, typename T2>
  void SinosoidalInOut(T * result, T start_value, T changeIn_value, 
                                T2 current_time, T2 duration)
  {
    *result = -changeIn_value / 2 * (cos(PI*current_time / duration) - 1) 
              + start_value;
  }

  template <typename T, typename T2>
  void QuadraticIn(T * result, T start_value, T changeIn_value, 
                         T2 current_time, T2 duration)
  {
    current_time /= duration;
    *result = changeIn_value*current_time*current_time + start_value;
  }

  template <typename T, typename T2>
  void QuadraticOut(T * result, T start_value, T changeIn_value, 
                          T2 current_time, T2 duration)
  {
    current_time /= duration;
    *result = -changeIn_value * current_time*(current_time - 2) + start_value;
  }

  template <typename T, typename T2>
  void QuadraticInOut(T * result, T start_value, T changeIn_value, 
                               T2 current_time, T2 duration)
  {
    current_time /= duration / 2;
    if (current_time < 1)
    {
      *result = changeIn_value / 2 * current_time*current_time + start_value;
    }
    else
    {
      --current_time;
      *result = -changeIn_value / 2 * (current_time*(current_time - 2) - 1) 
                + start_value;
    }
  }

  template <typename T, typename T2>
  void ExponentialIn(T * result, T start_value, T changeIn_value, 
                           T2 current_time, T2 duration)
  {
    *result = changeIn_value * static_cast<T>(pow(2, 10 * (current_time / duration - 1)))
              + start_value;
  }

  template <typename T, typename T2>
  void ExponentialOut(T * result, T start_value, T changeIn_value,
                            T2 current_time, T2 duration)
  {
    *result = changeIn_value * (-static_cast<T>(pow(2, -10 * current_time / duration)) + 1) 
              + start_value;
  }

  template <typename T, typename T2>
  void ExponentialInOut(T * result, T start_value, T changeIn_value, 
                                 T2 current_time, T2 duration)
  {
    current_time /= duration / 2;
    if (current_time < 1)
    {
      *result = changeIn_value / 2 * static_cast<T>(pow(2, 10 * (current_time - 1)))
                + start_value;
    }
    else
    {
      --current_time;
      *result = changeIn_value / 2 * (-static_cast<T>(pow(2, -10 * current_time)) + 2)
                + start_value;
    }
  }

  template <typename T, typename T2>
  void CircularIn(T * result, T start_value, T changeIn_value, 
                        T2 current_time, T2 duration)
  {
    current_time /= duration;
    *result = -changeIn_value * (sqrt(1 - current_time*current_time) - 1) 
               + start_value;
  }

  template <typename T, typename T2>
  void CircularOut(T * result, T start_value, T changeIn_value, 
                         T2 current_time, T2 duration)
  {
    current_time /= duration;
    --current_time;
    *result = changeIn_value * sqrt(1 - current_time*current_time) 
              + start_value;
  }

  template <typename T, typename T2>
  void CircularInOut(T * result, T start_value, T changeIn_value, 
                              T2 current_time, T2 duration)
  {
    current_time /= duration / 2;
    if (current_time < 1)
    {
      *result = -changeIn_value / 2 * (sqrt(1 - current_time*current_time) - 1) 
                + start_value;
    }
    else
    {
      current_time -= 2;
      *result = changeIn_value / 2 * (sqrt(1 - current_time*current_time) + 1) 
                + start_value;
    }
  }

  template <typename T, typename T2>
  void CubicIn(T * result, T start_value, T changeIn_value, 
                     T2 current_time, T2 duration)
  {
    current_time /= duration;
    *result = changeIn_value*current_time*current_time*current_time 
              + start_value;
  }

  template <typename T, typename T2>
  void CubicOut(T * result, T start_value, T changeIn_value, 
                      T2 current_time, T2 duration)
  {
    current_time /= duration;
    --current_time;
    *result = changeIn_value*(current_time*current_time*current_time + 1) 
              + start_value;
  }

  template <typename T, typename T2>
  void CubicInOut(T * result, T start_value, T changeIn_value, 
                           T2 current_time, T2 duration)
  {
    current_time /= duration / 2;
    if (current_time < 1)
    {
      *result = changeIn_value / 2 * current_time*current_time*current_time 
                + start_value;
    }
    else
    {
      current_time -= 2;
      *result = changeIn_value / 2 * (current_time*current_time*current_time + 2) 
                + start_value;
    }
  }

  template <typename T, typename T2>
  void QuarticIn(T * result, T start_value, T changeIn_value, 
                       T2 current_time, T2 duration)
  {
    current_time /= duration;
    *result = changeIn_value*current_time*current_time*current_time*current_time 
              + start_value;
  }

  template <typename T, typename T2>
  void QuarticOut(T * result, T start_value, T changeIn_value, 
                        T2 current_time, T2 duration)
  {
    current_time /= duration;
    --current_time;
    *result = -changeIn_value * (current_time*current_time*current_time*current_time - 1) 
              + start_value;
  }

  template <typename T, typename T2>
  void QuarticInOut(T * result, T start_value, T changeIn_value, 
                             T2 current_time, T2 duration)
  {
    current_time /= duration / 2;
    if (current_time < 1)
    {
      *result = changeIn_value / 2 * 
                current_time*current_time*current_time*current_time 
                + start_value;
    }
    else
    {
      current_time -= 2;
      *result = -changeIn_value / 2 *
                (current_time*current_time*current_time*current_time - 2)  
                + start_value;
    }
  }

  template <typename T, typename T2>
  void QuinticIn(T * result, T start_value, T changeIn_value, 
                       T2 current_time, T2 duration)
  {
    current_time /= duration;
    *result = changeIn_value*current_time*current_time*current_time*current_time*current_time 
              + start_value;
  }

  template <typename T, typename T2>
  void QuinticOut(T * result, T start_value, T changeIn_value, 
                        T2 current_time, T2 duration)
  {
    current_time /= duration;
    --current_time;
    *result = changeIn_value*
              (current_time*current_time*current_time*current_time*current_time + 1) 
              + start_value;
  }

  template <typename T, typename T2>
  void QuinticInOut(T * result, T start_value, T changeIn_value, 
                             T2 current_time, T2 duration)
  {
    current_time /= duration / 2;
    if (current_time < 1)
    {
      *result = changeIn_value / 2 * 
                current_time*current_time*current_time*current_time*current_time 
                + start_value;
    }
    else
    {
      current_time -= 2;
      *result = changeIn_value / 2 * 
                (current_time*current_time*current_time*current_time*current_time + 2) 
                + start_value;
    }
  }

}