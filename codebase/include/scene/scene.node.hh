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

#include <set>
#include <QObject>
#include <string>
#include <QString>
#include "matrix4.hh"


namespace clockwork {
namespace scene {

/**
 * @see scene.viewer.hh
 */
class Viewer;

/**
 * A branch node in the scene graph.
 */
class Node : public QObject
{
public:
   /**
    * Return the node's name.
    */
   const QString getName() const;
   /**
    * Set the node's name.
    * @param name the name to set.
    */
   void setName(const QString& name);
   /**
    * Return true if this node is pruned, false otherwise.
    */
   bool isPruned() const;
   /**
    * Prune this node.
    * @param pruned true if this node is to be pruned, false otherwise.
    */
   void setPruned(const bool pruned);
   /**
    * Return true if the node's name can be modified, false otherwise.
    */
   bool isNameEditable() const;
   /**
    * Add a child node.
    * @param node the child node to add.
    */
   void addChild(Node* const node);
   /**
    * Remove a child node.
    * @param node the child node to remove.
    */
   void removeChild(Node* const node);
   /**
    * Return the node's children.
    */
   const std::set<Node*>& getChildren() const;
   /**
    * Return the node's memory footprint in kibibytes (1 KiB = 1024 bytes).
    */
   //virtual clockwork::u64 getMemoryFootprint() const = 0;
   /**
    * Return the memory footprint in the form of a formatted string.
    */
   //const std::string& getMemoryFootprintAsString() const;
   /**
    * Update the node's geometry.
    * @param CMTM the current model transformation matrix.
    */
   virtual void updateGeometry(const clockwork::Matrix4& CMTM);
   /**
    * Render the node.
    * @param viewer the current scene viewer.
    */
   virtual void render(const Viewer& viewer) const;
protected:
   /**
    * Instantiate a node with a given name.
    * @param name the node's name.
    */
   Node(const std::string& name);
   /**
    * Make the node's name editable.
    * @param editable true if the node's name is editable, false otherwise.
    */
   void setNameEditable(const bool editable);
   /**
    * The node's children.
    */
   std::set<Node*> _children;
private:
   /**
    * True if this node's name can be edited, false otherwise.
    */
   bool _isNameEditable;
   /**
    * True if this node is pruned, false otherwise.
    */
   bool _isPruned;
};

} // namespace scene
} // namespace clockwork
