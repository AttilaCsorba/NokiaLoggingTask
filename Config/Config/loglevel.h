#pragma once
 class loglevel
{
	
public:
	enum log_level { DEBUG, INFO, WARNING, ERROR };
	log_level level;
	loglevel() {}
	loglevel(log_level l) {
		level = l;
	}
};

