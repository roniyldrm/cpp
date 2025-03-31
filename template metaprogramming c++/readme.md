SFINAE

The simplified idea is that the compiler will not generate an error while it tries to substitute the template types with the types you used in your code.
as long as there is some alternative way or candidate to replace them that will actually work.
In other words, if there are many candidates for an implementation, it is okay for them to fail to compile during type substitution, as long as there is another candidate that succeeds.


The goal of SFINAE is to select one implementation over the alternatives based on some "characteristic" or trait of the types used in the template.


sfiane allows to do introspection of classes (whether if a class has a specific method or not)