# Report - Python
The class PostcardList has been implemented, and passes all the tests.

## Functions
`writeFile` - opens self.file in write mode and writes the content of self.{date, from, to} as a human-readable string.
`readFile` - loops through the lines of the input file and appends them to self.postcards, then call parsePostcards method to
parse them. Notice the other members need to be reset.
`updateFile` - as writeFile but self.file is opened in append mode.
`updateLists` - as readFile but appending to self.postcards.

Notice that in all of the above functions the handling of files went through a context manager. Since Python lacks in the power
of destructors to implement RAII, context managers are a very useful tool in that every resource acquired within them is realeased
on exit.

`parsePostcards`- cycles through the postcards and updates the other attributes with their content, which can be easily achieved by calling the .find and .split methods of strings. The zip function is used to pair each postcard to an index.
`getNumberOfPostcards` - can be easily achieved by calling len, which under the hood calls the __len__ dunder method.
`getPostcardsByDateRange`- cycles thorugh each date, which is converted to a datetime.datetime object (by calling datetime.datetime.strptime with the adequate format as input), for which comparison operators work in the chronological sense. 
`getPostcardsByReceiver` and `getPostcardsbySender`- list comprehensions allow us to return in one line (they are faster, indentation does not matter inside of them, sometimes more readable). Notice the .get method of dictionaries has been used to deal with the situation in which a receiver/sender does not have any entry. 
