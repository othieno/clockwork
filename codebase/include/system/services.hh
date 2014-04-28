/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Jeremy Othieno.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#pragma once

#include <cstdint>
#include "execution.context.hh"
#include "concurrency.subsystem.hh"
#include "physics.subsystem.hh"
#include "graphics.subsystem.hh"
#include "resource.manager.hh"


namespace clockwork {
namespace system {

struct Services
{
   static clockwork::system::ExecutionContext               ExecutionContext;

//   static clockwork::system::AnimationSubsystem             Animation;
   static clockwork::system::PhysicsSubsystem               Physics;
   static clockwork::system::GraphicsSubsystem              Graphics;
   static clockwork::system::ConcurrencySubsystem           Concurrency;

   static clockwork::system::ResourceManager                Resource;

   static void                                              sleep(const uint64_t& milliseconds);
private:
                                                            Services(){}
                                                            Services(const Services&) = delete;
                                                            Services& operator=(const Services&) = delete;
};

} // namespace system
} // namespace clockwork
