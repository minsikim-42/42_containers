#include <ctime>
#include <vector>
#include <map>
#include <set>
#include "../../include/vector.hpp"
#include "../../include/map.hpp"
// #include "../../include/set.hpp"

void	efficiency_output(clock_t ft, clock_t std)
{
	double efficiency;

	if (std == 0 || ft == 0)
		std::cout << "🤨???" << (ft ? ft : std);
	else
	{
		efficiency = (double)std / (double)ft * 20;
		std::cout << (efficiency < 1 ? "😭 ; " : "😆 ; ") << efficiency << std::endl;
	}
}
