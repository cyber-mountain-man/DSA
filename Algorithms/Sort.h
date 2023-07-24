#ifndef SORT_H
#define SORT_H

#include <cstddef>
#include <cstdint>

template <typename T, typename Compare>
constexpr void insertion_sort(T* const arr, const size_t size, const Compare comp)
{
	if (size <= 1)
		return; // already sorted

	for (auto i = 1; i < size; ++i)
	{
		const T key = arr[i];
		auto j = i - 1;

		while (j >= 0 && comp(key, arr[j]))
		{
			arr[j + 1] = arr[j];
			arr[j--] = key;
		}
	}
}

template <typename T, typename Compare>
constexpr void merge_sort(T* const arr, const size_t left_index, const size_t right_index, const Compare comp)
{
	if (left_index >= right_index)
		return; // zero or one element

	const auto q = (left_index + right_index) / 2;

	merge_sort(arr, left_index, q, comp); // beginning - middle of arr
	merge_sort(arr, q + 1, right_index, comp); // middle - end of arr

	[&arr, left_index, right_index, &comp](const size_t mid)
	{
		const auto n1 = mid - left_index + 1;
		const auto n2 = right_index - mid;

		// create temp arrays
		T* const left_arr = new T[n1];
		T* const right_arr = new T[n2];

		// copy data to temp left array
		for (auto i = 0; i < n1; ++i)
			left_arr[i] = arr[left_index + i];

		// copy data to temp right array
		for (auto j = 0; j < n2; ++j)
			right_arr[j] = arr[mid + 1 + j];

		auto i = 0, j = 0;
		auto k = left_index;

		// merge the temp arrays back into arr[left..right]
		while (i < n1 && j < n2)
		{
			if (comp(left_arr[i], right_arr[j]))
				arr[k++] = left_arr[i++];
			else
				arr[k++] = right_arr[j++];
		}

		// copy the remaining elements of left array
		while (i < n1)
			arr[k++] = left_arr[i++];

		// copy the remaining elements of right array
		while (j < n2)
			arr[k++] = right_arr[j++];

		delete[] left_arr;
		delete[] right_arr;
	}(q);
}

template <typename T, typename Compare>
constexpr void selection_sort(T* const arr, const size_t size, const Compare comp)
{
	if (size <= 1)
		return; // already sorted

	auto min = 0;

	for (auto i = 0; i < size; ++i)
	{
		min = i;

		for (auto j = i + 1; j < size; ++j)
		{
			if (comp(arr[j], arr[min]))
				min = j;
		}

		if (min != i)
		{
			const T temp = arr[min];

			arr[min] = arr[i];
			arr[i] = temp;
		}
	}
}

template <typename T, typename Compare>
constexpr void bubble_sort(T* const arr, const size_t size, const Compare comp)
{
	if (size <= 1)
		return; // already sorted

	bool swapped = false;

	for (auto i = 0; i < size; ++i)
	{
		for (auto j = 0; j < size - i - 1; ++j)
		{
			if (comp(arr[j + 1], arr[j]))
			{
				const T temp = arr[j];

				arr[j] = arr[j + 1];
				arr[j + 1] = temp;

				swapped = true;
			}
		}

		if (!swapped)
			break; // no elements were swapped
	}
}

template <typename T, typename Compare>
constexpr void quick_sort(T* const arr, const int64_t left_index, const int64_t right_index, const Compare comp)
{
    if (left_index >= right_index)
        return;
        
       auto pivot = [&arr, left_index, right_index, &comp]() -> int64_t
       {
           auto i = left_index - 1;
           auto pivot = arr[right_index];

           for (auto j = left_index; j < right_index; ++j)
           {
               if (comp(arr[j], pivot))
               {
                   T temp = arr[++i];
                   arr[i] = arr[j];
                   arr[j] = temp;
               }
           }

           T temp = arr[++i];
           arr[i] = arr[right_index];
           arr[right_index] = temp;

           return i;
       }();
    
       quick_sort(arr, left_index, pivot - 1, comp);
       quick_sort(arr, pivot + 1, right_index, comp);
}

#endif // !SORT_H
