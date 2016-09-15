/*
 * This file is part of Clockwork.
 *
 * Copyright (c) 2014-2016 Jeremy Othieno.
 *
 * The MIT License (MIT)
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
#ifndef CLOCKWORK_IMAGE_FILTER_FACTORY_HH
#define CLOCKWORK_IMAGE_FILTER_FACTORY_HH

#include "ImageFilter.hh"
#include "Factory.hh"


namespace clockwork {
/**
 * The ImageFilterFactory is responsible for instantiating ImageFilter objects.
 */
class ImageFilterFactory : public Factory<ImageFilter::Identifier, ImageFilter> {
public:
	/**
	 *
	 */
	ImageFilterFactory(const ImageFilterFactory&) = delete;
	/**
	 *
	 */
	ImageFilterFactory(const ImageFilterFactory&&) = delete;
	/**
	 *
	 */
	ImageFilterFactory& operator=(const ImageFilterFactory&) = delete;
	/**
	 *
	 */
	ImageFilterFactory& operator=(const ImageFilterFactory&&) = delete;
	/**
	 * Returns the factory's unique instance.
	 */
	static ImageFilterFactory& getInstance();
private:
	/**
	 * Instantiates an ImageFilterFactory object.
	 */
	ImageFilterFactory() = default;
};
/**
 * @see Factory::create.
 */
template<> ImageFilter* Factory<ImageFilter::Identifier, ImageFilter>::create(const ImageFilter::Identifier&);
} // namespace clockwork

#endif // CLOCKWORK_IMAGE_FILTER_FACTORY_HH
