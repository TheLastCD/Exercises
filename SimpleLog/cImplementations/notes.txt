simpleLogger.c:
	Simplist logger, not threadsafe
	uses statically assigned date and time which is good if processing a batch of logs at the same time but in the case not needed
	this solution is not thread safe

inLineLogger.c:
	Removes the helper functions, which reduces modularity of the code
	the direct time and date calcs avoid the static array stuff with no real tradeoffs
	replaces the cReturnLevelchar function with a lookup table, this is quicker but also requires strict ordering of Enums, which since there aren't many isn't much of an issue
	moves to using localtime_r which is platform dependant but is what makes this solution thread safe


macroLogger.c:
	switches to using C macros as opposed to functions
		reducing function overhead
		easily compiled out if it where for release
		and access to certain compile time optimisations
	uses localtime_r again to enable thread safety
	faster mostly because as a macro it expands inline during preprocessing stage this negates:
		stack/frame creation and destruction
		parameter passing
		Return value handling
