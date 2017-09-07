/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _WIRING_INTERRUPTS_
#define _WIRING_INTERRUPTS_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//      LOW 0
//      HIGH 1
#define CHANGE 2
#define FALLING 3
#define RISING 4

#define DEFAULT 1
#define EXTERNAL 0

typedef void (*voidFuncPtr)(void);
typedef void (*voidFuncPtrParam)(void*);

/*
 * \brief Specifies a named Interrupt Service Routine (ISR) to call when an interrupt occurs.
 *        Replaces any previous function that was attached to the interrupt.
 */
void attachInterrupt(uint32_t pin, voidFuncPtr callback, uint32_t mode);
void attachInterruptParam(uint32_t pin, voidFuncPtrParam callback, uint32_t mode, void* param);

/*
 * \brief Turns off the given interrupt.
 */
void detachInterrupt(uint32_t pin);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#ifndef W_INTERRUPTS_CPP
#define W_INTERRUPTS_CPP

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <functional>
#include "wiring_private.h"

#define __maybe_unused  __attribute__((unused))

template <typename T>
using voidTemplateFuncPtrParam =  void (*)(T param);

template<typename T> struct __container__ {
  void* param;
  voidTemplateFuncPtrParam<T>* function;
};

// C++ only overloaded version of attachInterrupt function
template<typename T> void attachInterrupt(uint8_t interruptNum, voidTemplateFuncPtrParam<T> userFunc, int mode, T& param) {

  auto callback=[&](){
    userFunc(param);
  };
  auto thunk=[](void* arg){ // note thunk is captureless
    (*static_cast<decltype(callback)*>(arg))();
  };

  attachInterruptParam(interruptNum, thunk, mode, &callback);
}

template<typename T> void attachInterrupt(uint8_t interruptNum, voidTemplateFuncPtrParam<T*> userFunc, int mode, T* param) {
  attachInterruptParam(interruptNum, (voidFuncPtrParam)userFunc, mode, (void*)param);
}

#endif
#endif

#endif
