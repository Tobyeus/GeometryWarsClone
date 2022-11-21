#pragma once
#include <string>

class Action {
	std::string m_name = "None";
	// Types will Press and Release
	std::string m_type = "None";
public:
	Action(std::string& name, std::string& type): 
		m_name(name),
		m_type(type) {}

	std::string& getType() { return m_type; };
	std::string& getName() { return m_name; };
};