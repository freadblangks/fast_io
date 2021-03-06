#include"../../timer.h"
#include"../../../include/fast_io.h"
#include"../../../include/fast_io_device.h"
//#include"../../include/fast_io_crypto.h"
#include"../../../include/fast_io_legacy.h"
#include<random>
#include<thread>

int main()
{
	constexpr std::size_t N(10000000);
	std::vector<double> vec;
	vec.reserve(N);
	std::random_device device;
	std::mt19937_64 eng;
	std::uniform_real_distribution dis(-1000.0,1000.0);
	for(std::size_t i(0);i!=N;++i)
		vec.emplace_back(dis(eng));
	{
	fast_io::timer t("obuf file normal output");
	fast_io::obuf_file obf("obuf_file_normal_scientific.txt");
	for(std::size_t i{};i!=N;++i)
		println(obf,fast_io::scientific(vec[i]));
	}

	{
	fast_io::timer t("parallel output");
	fast_io::obuf_file obf("parallel_scientific.txt");
	print(obf,fast_io::parallel(vec,[](auto const& e)
	{
		return fast_io::line(fast_io::scientific(e));
	}));
	}
}