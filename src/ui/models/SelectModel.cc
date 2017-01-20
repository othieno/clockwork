/*
 * This file is part of Clockwork.
 *
 * Copyright (c) 2013-2017 Jeremy Othieno.
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
#include "SelectModel.hh"
#include "enum_traits.hh"

using clockwork::SelectModel;


SelectModel::SelectModel(QObject* parent) :
QAbstractListModel(parent) {}


SelectModel::SelectModel(const QList<Option>& options, QObject* parent) :
QAbstractListModel(parent),
options_(options) {}


SelectModel::Option::Option(const QString& l, const QVariant& v) :
label(l),
value(v) {}


QHash<int, QByteArray>
SelectModel::roleNames() const {
	using enum_traits = enum_traits<SelectModel::Role>;
	return {
		{enum_traits::ordinal(Role::Label), "label"},
		{enum_traits::ordinal(Role::Value), "value"},
	};
}


int
SelectModel::rowCount(const QModelIndex&) const {
	return options_.count();
}


QVariant
SelectModel::data(const QModelIndex& index, const int role) const {
	const auto row = index.row();
	if (row >= 0 && row < options_.count()) {
		using enum_traits = enum_traits<SelectModel::Role>;

		const auto& item = options_[row];
		switch (enum_traits::enumerator(role)) {
			case Role::Label:
				return item.label;
			case Role::Value:
				return item.value;
			default:
				break;
		}
	}
	return QVariant();
}


const QList<SelectModel::Option>&
SelectModel::getOptions() const {
	return options_;
}


void
SelectModel::setOptions(const QList<Option>& options) {
	options_ = options;
}


QStringList
SelectModel::getLabels() const {
	QStringList labels;
	for (const auto& option : options_) {
		labels << option.label;
	}
	return labels;
}


QVariantList
SelectModel::getValues() const {
	QVariantList values;
	for (const auto& option : options_) {
		values << option.value;
	}
	return values;
}
