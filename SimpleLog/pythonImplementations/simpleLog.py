import datetime


class Logger():
    def __init__(self, level):
        self.filter = LogEnum.EnumLevel[0: level]

    def ReturnDateTime(self):
        return str(datetime.datetime.now())

    def Log(self, Level, Text):
        if Level in self.filter:
            print(self.ReturnDateTime(), Level, Text)


class LogEnum():
    WARN = "WARN"
    INFO = "INFO"
    ERROR = "ERROR"
    UNKNOWN = "UNKNOWN"

    EnumLevel = [UNKNOWN, ERROR, WARN, INFO]


log = Logger(4)

log.Log(LogEnum.WARN, "this is an warning log")
log.Log(LogEnum.INFO, "this is an info log")
log.Log(LogEnum.ERROR, "this is an error log")
log.Log(LogEnum.UNKNOWN, "this is an unknown log")
