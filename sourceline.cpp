#include "sourceline.h"

int LineError::getColumn()
{
	return m_column;
}
std::string LineError::getError()
{
	return m_errorMsg;
}
void LineError::set(int col, const std::string& err)
{
	m_column = col;
	m_errorMsg = err;
}	

SourceLine::SourceLine()
{
	m_lineNo = 1;				
	clearLine();			
}
void SourceLine::buildLine(const std::string& str) // builds the line
{
	m_line += str;
	m_firstLexemeColumn = m_lastLexemeColumn + 1;
	m_lastLexemeColumn = m_firstLexemeColumn + str.size() - 1;
}
bool SourceLine::hasError() // if there an error recorded?
{
	return !m_errors.empty();
}
void SourceLine::addError(const std::string& msg) // sets an error message
{
	if(m_errors.size() >= MAX_ERRORS_IN_LINE)
		return;
	// Check if repeated on same column, then skip
	if(!m_errors.empty() && m_firstLexemeColumn == m_errors[m_errors.size()-1].getColumn())
		return;
	LineError error;
	error.set(m_firstLexemeColumn, msg);
	m_errors.push_back(error);
}
void SourceLine::printLine() // prints the line and error messages in line if any
{
	printf("% 7d : %s\n", m_lineNo, m_line.c_str());
	if(!m_errors.empty())
		printErrors();
}
void SourceLine::newLine()
{
	m_lineNo++;
	clearLine();
}
void SourceLine::clearLine() // clears the line
{
	m_line.clear();		
	m_errors.clear();
	m_firstLexemeColumn = 0;	
	m_lastLexemeColumn = 0;		
}
void SourceLine::printErrors()
{
	for(std::size_t n = 0 ; n < m_errors.size() ; n++)
	{
		printf("          ");  // Padding for line number and seperator.
		for(int i = 1 ; i < m_errors[n].getColumn() ; i++)
		{
			printf(" ");  // Padding to reach error column
		}
		printf("^ %s\n", m_errors[n].getError().c_str());
	}
}

