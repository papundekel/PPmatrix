#pragma once
#include "compressed_pair.hpp"
#include "matrix_view.hpp"

namespace PPmatrix
{
	template <typename Iterator, typename Sentinel>
	class simple_matrix_view
	{
		std::size_t width_;
		compressed_pair<Iterator, Sentinel> pair;

	public:
		template <typename View>
		constexpr simple_matrix_view(View&& view, std::size_t width)
			: width_(width)
			, pair{ PPmatrix::begin(view), PPmatrix::end(view) }
		{}
		template <typename MatrixView>
		constexpr simple_matrix_view(MatrixView&& view)
			: simple_matrix_view(view, PPmatrix::width(view))
		{}
		constexpr simple_matrix_view(Iterator begin, Sentinel end, std::size_t width)
			: width_(width)
			, pair{ begin, end }
		{}
		constexpr auto begin() const
		{
			return pair.first;
		}
		constexpr auto end() const
		{
			return pair.second;
		}
		constexpr auto width() const
		{
			return width_;
		}

		constexpr auto set_width(std::size_t width)
		{
			width_ = width;
		}
	};
	template <typename MatrixView>
	simple_matrix_view(MatrixView&&)->simple_matrix_view<begin_t<MatrixView>, end_t<MatrixView>>;
	template <typename View>
	simple_matrix_view(View&&, std::size_t)->simple_matrix_view<begin_t<View>, end_t<View>>;
}