#ifndef UTILS_SPECTRAL
#define UTILS_SPECTRAL
#include<vector>
#include<numeric>
#include<string>
#include<regex>
#include<vector>



std::vector<std::string >  splitString(std::string line ){
	std::vector<std::string> vs; 
	std::regex rgx("\\s+");
	std::sregex_token_iterator iter(line.begin(), line.end(), rgx, -1 ) ;
	std::sregex_token_iterator end;
	while( iter != end  ) {
		vs.push_back(*iter);
		iter++; 
	}
	return vs;
}

template < class T > std::ostream& operator << ( std::ostream& os , const std::vector< T  >& v ) {

	os << " { " << std::endl;

	for( auto e : v  ) 
	{
		os << " > " ;
		os << e << " ";
		os << std::endl;
	}

	os << " } " << std::endl;

	return os; 
}

template < class T > std::ostream& operator << ( std::ostream& os , const std::vector<std::vector< T > >& v ) {

	os << " { " << std::endl;

	for( auto e : v  ) 
	{
		os << " > " ;
		for ( auto f : e ) 
			os << f << " ";
		os << std::endl;
	}

	os << " } " << std::endl;

	return os; 
}

template<class T> double mean(std::vector<T> c) {
	return std::accumulate(c.begin(), c.end() , 0)  /c.size(); 
}

#endif
