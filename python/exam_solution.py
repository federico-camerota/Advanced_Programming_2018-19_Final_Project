# python/exam_solution.py

class PostcardsList:

    def __init__(self, file_name):
        self._file = file_name
        self._postcards = list()
        self._date = dict()
        self._from = dict()
        self._to = dict()

    def writeFile(self):

        with open(self._file, 'w') as file_handler:
            for  x in self._date:
                file_handler.write(x + ' : ' + str(self._date[x]) + '\n')
            for x in self._from:
                file_handler.write(x + ' : ' + str(self._from[x]) + '\n')
            for x in self._to:
                file_handler.write(x + ' : ' + str(self._to[x]) + '\n')

    def readFile(self, file_name = None):

        if file_name == None:
            file_name = self._file








