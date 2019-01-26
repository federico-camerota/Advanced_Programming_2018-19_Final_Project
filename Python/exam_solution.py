# python/exam_solution.py

import datetime


class PostcardList:

    def __init__(self):
        self._file = None
        self._postcards = list()
        self._date = dict()
        self._from = dict()
        self._to = dict()

    def writeFile(self):
        '''
        Write self.{_date,_from,_to} to self._file
        '''
        with open(self._file, 'w') as file_handler:
            for  x in self._date:
                file_handler.write(x + ' : ' + str(self._date[x]) + '\n')
            for x in self._from:
                file_handler.write(x + ' : ' + str(self._from[x]) + '\n')
            for x in self._to:
                file_handler.write(x + ' : ' + str(self._to[x]) + '\n')

    def readFile(self, file_name):
        '''
        From self._file read self.{_date,_from,_to}
        '''
        #set file attribute
        self._file = file_name
        #reset other attributes
        self._postcards = list()
        self._date = dict()
        self._from = dict()
        self._to = dict()

        #read postcards from file
        with open(file_name, 'r') as file_handler:

            for line in file_handler:
                self._postcards.append(line)

        #parse postcards
        self.parsePostcards()

    def parsePostcards(self):
        '''
        Parse self._postcards, set self.{_date,_from,_to}
        '''
        line_num = 0
        for postcard in self._postcards:

            #line_num += 1
            #extract fields
            fields = postcard.split(';')
            date = fields[0][fields[0].find(':') + 1 :]
            line_from = fields[1][fields[1].find(':') + 1 :]
            to = fields[2][fields[2].find(':') + 1 :]
            #add date
            if date not in self._date:
                self._date[date] = [line_num]
            else:
                self._date[date].append(line_num)
            #add from
            if line_from not in self._from:
                self._from[line_from] = [line_num]
            else:
                self._from[line_from].append(line_num)
            #add to
            if to not in self._to:
                self._to[to] = [line_num]
            else:
                self._to[to].append(line_num)
            line_num += 1

    def updateFile(self):
        '''
        As write but appending to self._file
        '''
        with open(self._file, 'a') as file_handler:
            for  x in self._date:
                file_handler.write(x + ' : ' + str(self._date[x]) + '\n')
            for x in self._from:
                file_handler.write(x + ' : ' + str(self._from[x]) + '\n')
            for x in self._to:
                file_handler.write(x + ' : ' + str(self._to[x]) + '\n')

    def updateLists(self, file_name):
        '''
        As read but appending to self._postcards
        '''
        #update file
        self._file = file_name

        #append new postcards
        with open(file_name, 'r') as file_handler:

            for line in file_handler:
                self._postcards.append(line)

        self._date = dict()
        self._from = dict()
        self._to = dict()

        #parse postcards
        self.parsePostcards()

    def getNumberOfPostcards(self):
        '''
        Returns length of self._postcards
        '''
        return len(self._postcards)

    def getPostcardsByDateRange(self, date_range):
        '''
        Returns the postcards within a date_range
        '''
        ans = set()    #using a set avoids dealing with repetitions
        start, end = date_range
        for date, index_list in self._date.items():
            ans.update([self._postcards[num] for num in index_list if start <= datetime.datetime.strptime(date, "%Y-%m-%d") <= end])
        return list(ans)

    def getPostcardsBySender(self, sender):
        '''
        Returns the postcards from a sender
        '''
        return [self._postcards[num] for num in range(self.getNumberOfPostcards()) if num in self._from.get(sender, [])]

    def getPostcardsByReceiver(self, receiver):
        '''
        Returns the postcards to a receiver
        '''
        return [self._postcards[num] for num in range(self.getNumberOfPostcards()) if num in self._to.get(receiver, [])]


