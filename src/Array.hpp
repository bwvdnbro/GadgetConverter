/*******************************************************************************
 * This file is part of GadgetConverter
 * Copyright (C) 2016 Bert Vandenbroucke (bert.vandenbroucke@gmail.com)
 *
 * GadgetConverter is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GadgetConverter is distributed in the hope that it will be useful,
 * but WITOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with GadgetConverter. If not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/

/**
 * @file Array.hpp
 *
 * @brief Fixed size array that can be passed along as a parameter
 *
 * @author Bert Vandenbroucke (bert.vandenbroucke@ugent.be)
 */
#ifndef ARRAY_HPP
#define ARRAY_HPP

/**
 * @brief Fixed size array
 *
 * When using compiler optimization flags, an Array is exactly identical to
 * a plain C array. However, since it is an object, you don't have to pass
 * around pointers and it is more clear what size an input array to a routine
 * will have.
 */
template <typename T, unsigned int N> class Array {
private:
  /**
   * @brief The actual plain C array that is stored in memory
   */
  T _array[N];

public:
  /**
   * @brief Constructor
   *
   * Initializes an empty Array
   */
  inline Array() {
    for (unsigned int i = 0; i < N; ++i) {
      _array[i] = 0;
    }
  }

  /**
   * @brief Copy constructor
   *
   * Creates a new Array with the same contents as the given Array. The
   * contents are copied, so that it is safe to manipulate the old Array
   * afterwards.
   *
   * @param a Array to be copied
   * @return Reference to the newly created Array
   */
  inline Array &operator=(const Array &a) {
    for (unsigned int i = 0; i < N; ++i) {
      _array[i] = a._array[i];
    }
    return *this;
  }

  /**
   * @brief Copy constructor
   *
   * Creates a new Array with the same contents as the given Array. The
   * contents are copied, so that it is safe to manipulate the old Array
   * afterwards.
   *
   * @param a Array to be copied
   */
  inline Array(Array &a) {
    for (unsigned int i = 0; i < N; ++i) {
      _array[i] = a._array[i];
    }
  }

  /**
   * @brief Access operator
   *
   * Returns a reference to the index-th element of the Array. This is
   * identical to manipulating the underlying plain C array.
   *
   * @param index Index of the element of the array that is accessed
   * @return Reference to the element at the given position in the Array
   */
  inline T &operator[](unsigned int index) { return _array[index]; }

  /**
   * @brief Dereference operator
   *
   * Return a pointer to a bitwise representation of the Array that can be
   * used for binary input/output.
   *
   * @return Pointer to a binary representation of the Array
   */
  inline operator char *() { return reinterpret_cast<char *>(_array); }

  /**
   * @brief Get the size in memory of the Array
   *
   * Returns the size (in bytes) in memory of the underlying C array. This
   * corresponds to the size of the array pointed to by the return value of
   * operator char*().
   *
   * @return Size (in bytes) of the array in memory
   */
  inline unsigned int memsize() { return N * sizeof(T); }
};

#endif // ARRAY_HPP
