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
#ifndef CLOCKWORK_SELECT_MODEL_HH
#define CLOCKWORK_SELECT_MODEL_HH

#include <QAbstractListModel>

namespace clockwork {
/**
 * The SelectModel is a list model that is designed to contain a set of
 * options, where each option is a <label, value> pair.
 */
class SelectModel : public QAbstractListModel {
	Q_OBJECT
	Q_PROPERTY(int length READ rowCount CONSTANT)
	Q_PROPERTY(QStringList labels READ getLabels CONSTANT)
public:
	/**
	 *
	 */
	enum class Role {
		Label = Qt::UserRole + 1,
		Value
	};
	/**
	 *
	 */
	struct Option {
		/**
		 * Instantiates an Option object with the specified label and value.
		 * @param label the options's label.
		 * @param value the options's value.
		 */
		Option(const QString& label, const QVariant& value);
		/**
		 * The option's label.
		 */
		const QString label;
		/**
		 * The option's value.
		 */
		const QVariant value;
	};
	/**
	 * Instantiates a SelectModel object.
	 * @param parent the model's parent.
	 */
	explicit SelectModel(QObject* parent);
	/**
	 * Instantiates a SelectModel object with the specified set of options.
	 * @param options the model's set of options.
	 * @param parent the model's parent.
	 */
	explicit SelectModel(const QList<Option>& options, QObject* parent);
	/**
	 * @see QAbstractItemModel::roleNames.
	 */
	QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;
	/**
	 * @see QAbstractItemModel::rowCount.
	 */
	int rowCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;
	/**
	 * @see QAbstractItemModel::data.
	 */
	QVariant data(const QModelIndex& index, const int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
	/**
	 * Returns the set of available options.
	 */
	const QList<Option>& getOptions() const;
	/**
	 * Sets the model's options.
	 * @param options the list of options to set.
	 */
	void setOptions(const QList<Option>& options);
	/**
	 * Returns the list of option labels.
	 */
	QStringList getLabels() const;
private:
	/**
	 * The set of available options.
	 */
	QList<Option> options_;
};
} // namespace clockwork

#endif // CLOCKWORK_SELECT_MODEL_HH
