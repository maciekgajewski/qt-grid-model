// (C) Maciej Gajewski, 2016

#include <benchmark/benchmark.h>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/hashed_index.hpp>

#include <cstdint>
#include <random>\

struct random_access_tag {};
struct hashed_tag {};

namespace bmi = boost::multi_index;

template<typename T>
using multiindex_container_t = boost::multi_index_container<
	T,
	bmi::indexed_by<
		bmi::random_access<bmi::tag<random_access_tag>>,
		bmi::hashed_non_unique<bmi::tag<hashed_tag>, bmi::identity<std::uint64_t>>
		>
	>;

template<typename T>
class container_t
{
public:

	void reserve(size_t s) { mMI.reserve(s); }
	void push_back(const T& v) { mMI.push_back(v); }

	size_t index_of(const T& v)
	{
		auto& hash_index = boost::get<hashed_tag>(mMI);
		auto& random_index = boost::get<random_access_tag>(mMI);

		auto hash_it = hash_index.find(v);
		if (hash_it == hash_index.end())
			throw std::runtime_error("no such element: " + std::to_string(v));

		const T& found = *hash_it;
		auto random_it = random_index.iterator_to(found);
		return random_it - random_index.begin();
	}

private:

	multiindex_container_t<T> mMI;
};

template<typename T>
class naive_t
{
public:

	void reserve(size_t s) { mV.reserve(s); }
	void push_back(const T& v) { mV.push_back(v); }

	size_t index_of(const T& v)
	{
		auto it = std::find(mV.begin(), mV.end(), v);
		if (it == mV.end())
			throw std::runtime_error("no such element: " + std::to_string(v));

		return it - mV.begin();

	}

private:

	std::vector<T> mV;
};

template<typename Container>
Container create(std::uint64_t size)
{
	Container container;
	container.reserve(size);

	for(std::uint64_t i = 0; i < size; i++)
		container.push_back(i);

	return container;
}

template<typename Container>
static void indexof_becnhmark(benchmark::State& state)
{
	std::uint64_t size = state.range_x();
	Container container = create<Container>(size);
	std::default_random_engine random;
	std::uniform_int_distribution<std::uint64_t> dist(0, size-1);

	while (state.KeepRunning())
	{
		std::uint64_t search = dist(random);
		size_t idx = container.index_of(search);
		if (idx != search)
			throw std::runtime_error("Search failed");
	}
}

BENCHMARK_TEMPLATE(indexof_becnhmark, container_t<std::uint64_t>)->Range(16, 16<<20);
BENCHMARK_TEMPLATE(indexof_becnhmark, naive_t<std::uint64_t>)->Range(16, 16<<20);

BENCHMARK_MAIN();
