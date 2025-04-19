/*
Copyright 2020 Google LLC. Modified by biazo

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    https://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#pragma once

#include <inttypes.h>
#include <string>
#include <memory>
#include "instrumentation.h"

class TinyInstInstrumentation : public Instrumentation
{
public:
  ~TinyInstInstrumentation();

  void Init(int argc, char **argv) override;

  RunResult Run(int argc, char **argv, uint32_t init_timeout,
                uint32_t timeout) override;
  RunResult RunWithCrashAnalysis(int argc, char **argv, uint32_t init_timeout,
                                 uint32_t timeout) override;

  void CleanTarget() override;

  bool HasNewCoverage() override;
  void GetCoverage(Coverage &coverage, rust::Vec<uint64_t> &afl_coverage, bool clear_coverage) override;
  void ClearCoverage() override;
  void IgnoreCoverage(Coverage &coverage) override;

  uint64_t GetReturnValue() override;

  std::string GetCrashName() override;
  std::string GetCrashNameValue();
  std::unique_ptr<std::string> GetCrashNameOwned();
  std::unique_ptr<std::string> GetCrashNameValueOwned();

private:
  std::string crash_name_;

protected:
  AFLCov *instrumentation;
  bool persist;
  int num_iterations;
  int cur_iteration;
};
