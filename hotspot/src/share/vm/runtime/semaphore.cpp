/*
 * Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 *
 */

#include "precompiled.hpp"
#include "utilities/debug.hpp"
#include "runtime/semaphore.hpp"

/////////////// Unit tests ///////////////

#ifndef PRODUCT

static void test_semaphore_single_separate(uint count) {
  Semaphore sem(0);

  for (uint i = 0; i < count; i++) {
    sem.signal();
  }

  for (uint i = 0; i < count; i++) {
    sem.wait();
  }
}

static void test_semaphore_single_combined(uint count) {
  Semaphore sem(0);

  for (uint i = 0; i < count; i++) {
    sem.signal();
    sem.wait();
  }
}

static void test_semaphore_many(uint value, uint max, uint increments) {
  Semaphore sem(value);

  uint total = value;

  for (uint i = value; i + increments <= max; i += increments) {
    sem.signal(increments);

    total += increments;
  }

  for (uint i = 0; i < total; i++) {
    sem.wait();
  }
}

static void test_semaphore_many() {
  for (uint max = 0; max < 10; max++) {
    for (uint value = 0; value < max; value++) {
      for (uint inc = 1; inc <= max - value; inc++) {
        test_semaphore_many(value, max, inc);
      }
    }
  }
}

void test_semaphore() {
  for (uint i = 1; i < 10; i++) {
    test_semaphore_single_separate(i);
  }

  for (uint i = 0; i < 10; i++) {
    test_semaphore_single_combined(i);
  }

  test_semaphore_many();
}

#endif // PRODUCT

