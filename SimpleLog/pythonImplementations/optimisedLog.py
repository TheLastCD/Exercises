
from enum import Enum
from datetime import datetime
from functools import lru_cache


class LogLevel(Enum):
    UNKNOWN = 0
    ERROR = 1
    WARN = 2
    INFO = 3


class Logger:
    def __init__(self, level: LogLevel):
        self.filter_level = level.value

    @staticmethod
    @lru_cache(maxsize=1)
    def getCurrentTime():
        return datetime.now().strftime("%Y-%m-%d %H:%M:%S")

    def Log(self, level: LogLevel, text: str):
        if level.value <= self.filter_level:
            print(f"{self.getCurrentTime()} [{level.name}] {text}")


# Usage
logger = Logger(LogLevel.INFO)

logger.Log(LogLevel.WARN, "This is a warning log")
logger.Log(LogLevel.INFO, "This is an info log")
logger.Log(LogLevel.ERROR, "This is an error log")
logger.Log(LogLevel.UNKNOWN, "This is an unknown log")
