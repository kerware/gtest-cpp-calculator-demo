#!/usr/bin/env bash
set -euo pipefail
./build/calculator_tests --gtest_list_tests
./build/calculator_tests --gtest_filter='BeginnerAssertions.*'
./build/calculator_tests --gtest_filter='*DeathTests*' --gtest_death_test_style=threadsafe
./build/calculator_tests --gtest_repeat=3 --gtest_shuffle --gtest_random_seed=42
./build/calculator_tests --gtest_output=xml:build/gtest-report.xml
