---
layout: post
title: Python - Intro to Classes
tags: 
categories:
  - Blog
date: 2025-07-20
updated: 2025-07-20T21:48
created: 2025-07-20T21:45
---
Welcome to the first of what will be a series of articles talking about what is great about Python, and what is not so great. Even though I am a fan of the language, I am not so enamored as to be blind to its weaknesses. So over the coming months we will not only learn about how to do certain tasks in Python, but also what pitfalls you may run into during your travels. Once we have some Python basics under our collective belts, we will start looking at ways to apply this new found knowledge and code some programs up for the Raspberry Pi. The Raspberry Pi is one of the low cost educational boards out there that you can experiment on. The first subject we will look at is using objects in Python. According to the official documentation, objects are Python's abstraction for data. All data in a Python program is represented by objects or by relations between objects. Actually, almost everything in Python is an object. So learning a bit more about how they behave is important to developing code of any real value. More specifically, we will look at classes and how to work with objects of your own design.

Classes in Python support all of the most common concepts in Object Oriented Programming. The mechanisms of classes in Python were inspired by C++ and Modula-3. A class can inherit from multiple base classes and can override any methods in the base classes. All of the methods in the base classes are also available to be called from the inheriting class. As for data, objects can contain arbitrary amounts and types. And because Python is a dynamic language, all of this is modifiable at run-time. As an example, let's say that you want to develop a program that will do some kind of geometric processing. One of the core objects that you will want to use is likely something that represents a point. Looking at two dimensional geometry first, you will need to store two values, an x and a y. In code, this would look like

```python
   class Point:
      pass
```

This gives us a blank class called Point. The first line is how you define a new class. It is very similar to how you define a new function, except that you exchange the keyword 'def' with the keyword 'class'. A class always needs to have at least one statement. If you don't want your new class to do anything yet, you can use the keyword 'pass'. This essentially tells Python, "don't do anything here". You can now use this class to create new objects of type Point. You can do this with

```python
   my_point = Point()
```

This is not really all that useful yet. There is nowhere to store our point values. Or is there? One of the really cool things about Python objects is that they are fully dynamic. You can add x and y values with the statements

```python
   my_point.x = 10.0
   my_point.y = 20.0
```

This particular instance of the Point class now has an x and y value. Unfortunately, we can't really use them effectively. It would be better to have them as part of the definition of the class so that we can write methods that know how to use this data. It many cases, it also makes sense to initialize these variables. One way to do this is to simply write statements within the class definition directly.

```python
   class Point:
      x = 0.0
      y = 0.0
```

The other way to initialize values is to use the __init__ method in classes. This method gets automatically called when a new object gets instantiated. This looks like

```python
   class Point:
      def __init__(self):
         x = 0.0
         y = 0.0
```

You can then set your values for x and y after creating a new instance with

```python
   my_point = Point()
   my_point.x = 10.0
   my_point.y = 20.0
```

While this works well, one thing to remember is that programmers are inherently lazy and do not want to type more than absolutely necessary. Following this idea, it would be great if you could assign your x and y values at the same time you are creating a new object. In Python, you can. The __init__ function can be written to take parameters.

```python
   class Point:
      def __init__(self, xvalue, yvalue):
         self.x = xvalue
         self.y = yvalue
```

So your code simplifies down to

```python
   my_point = Point(10.0, 20.0)
```

Isn't that much easier? Now that you have a point defined, you can add methods to work on this data. One of the first methods for a point is its absolute value. To add this to your class, you can just add the function definition to the class definition with

```python
   class Point:
      def __init__(self, xvalue, yvalue):
         self.x = xvalue
         self.y = yvalue
      def abs_val(self):
         sqr_val = self.x**2 + self.y**2
         return sqr_val**0.5
```

Now that you have a basic two dimensional point defined, you may want to create objects that can handle three dimensional points. Code reuse is something that should be aimed for, and easy to do in Python. You can create a new class that builds on the existing code for two dimensional points. This would look like

```python
   class ThreeDPoint(Point):
      def __init__(self, xvalue, yvalue, zvalue):
         self.x = xvalue
         self.y = yvalue
         self.z = zvalue
```

Written this way, the initialization method has been overridden to take three parameters rather than two. But, nothing has been done to the method abs_val, inherited from the Point subclass. So when you call this from an instantiated ThreeDPoint object, you will get the length of the x and y parts of this point. If you want a proper three dimensional absolute value, you will need to override the abs_val function.

Now that you've seen how to create your own objects, next month we'll look at some details around how Python manages these objects in memory. On most desktop systems, memory is not really a concern. But the Raspberry Pi is relatively constrained, so knowing how memory is handled will become more important for your code.
