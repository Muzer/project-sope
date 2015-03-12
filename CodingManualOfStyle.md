This should be followed strictly by everyone. All of these standards are followed by most professional, high-quality programs, so there shouldn't really be any arguments.

# Indentation and line length #

One level of indentation is four spaces. No tabs. Ever. Ever. Ever. This is the default in QtCreator


Lines should be no longer than 80 characters unless they really really have to. Remember, use the fact that C++ lines are terminated by a semicolon, not a newline, to your advantage. You can enable an 80-character margin in QtCreator to allow you to see the limit.

This is in order to:

> a) Keep the code nice and readable (word wrapping generally wraps in the wrong place or bad places and makes it horrible to read, no word wrapping means you must horizontally scroll)

> b) Make sure no problems occur when sending plain-text e-mail

> c) Keep in line with the vast majority of other high-quality programs (most of them have 80 or 78-character limits)


# Open braces #

These should go on the line after the declaration line. Close braces should go on their own line

# If/for/while statements with a single command to execute #

Unless you know you'll be expanding things, to keep these neat, don't bother with the braces, just indent the single command and place it on the next line with a semicolon at the end.

# Comments #

// should be used for ordinary comments

// should be used for commenting out code.

There are reasons for this, look them up.



Code should only be commented if it is not obvious from looking what it does. Also, short "sections" should be commented to show what they do in the bigger picture.



Markers should be put in comments where necessary:

FIXME to mark potential problematic code that requires special attention and/or review (eg settings hardcoded rather than XML'd)

NOTE to document inner workings of code and indicate potential pitfalls.

TODO to indicate planned enhancements.

XXX to warn other programmers of problematic or misguiding code.