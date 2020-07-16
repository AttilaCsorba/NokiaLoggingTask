This logging library works using Boost libraries, more precisely 
boost_1_73_0-msvc-14.2-32.

Configuration rules:
	console_logging 
		-enables/disables console logging
		-should be set to TRUE/FALSE
	console_format
		-sets formatting for console output
		-should be set corresponding to boost formatting 
	console_level
		-sets the log level for console writing
		-settings are DEBUG, INFO, WARNING, ERROR
	file_logging
		-enables/disables file logging
		-should be set to TRUE/FALSE
	file_name
		-sets the filename pattern
	rotation
		-enables/disables file rotation
		-should be set to TRUE/FALSE
	file_full
		-sets max file size in Mib
	file_max
		-sets max number of files
	file_format
		-sets formatting for file output
		-should be set corresponding to boost formatting 
	console_level
		-sets the log level for file writing
		-settings are DEBUG, INFO, WARNING, ERROR

Functions:
	log()
		-parameters are message, log level, and source
		-creates a log
	getErrors()
		-returns all active errors
	clear()
		-expects id as parameter
		-clears log entry with id