/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2013 Jeremy Othieno.
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
#include "error.hh"
#include "execution.context.hh"
#include "concurrency.subsystem.hh"
#include "graphics.subsystem.hh"
#include "asset.manager.hh"


namespace clockwork {
namespace system {

class Services
{
public:
	/**
	 * The application's execution context.
	 */
	 static clockwork::system::ExecutionContext Context;
	/**
	 * The concurrency subsystem.
	 */
	static clockwork::concurrency::ConcurrencySubsystem Concurrency;
	/**
	 * The graphics subsystem.
	 */
	static clockwork::graphics::GraphicsSubsystem Graphics;
	/**
	 * The asset manager.
	 */
	static clockwork::system::AssetManager Assets;
	/**
	 * Initialise the services.
	 * @param context the execution context that the application will be executed in.
	 */
	static clockwork::Error initialise(const int& argc, const char** const argv);
	/**
	 * Update all subsystems.
	 */
	static void update();
	/**
	 * Cleanup the services.
	 * @param applicationExitError the error returned when the application exited.
	 */
	static clockwork::Error dispose(const clockwork::Error& applicationExitError);
	/**
	 * Block the current thread execution for a given duration.
	 * @param milliseconds the number of milliseconds to block thread execution.
	 */
	static void sleep(const int64_t& milliseconds);
private:
	/**
	 * Create an execution context from command line arguments.
	 * @param argc the number of command line arguments.
	 * @param argv the array containing command line arguments passed to the program.
	 */
	static void buildExecutionContext(const int& argc, const char** const argv);
};

} // namespace system
} // namespace clockwork
