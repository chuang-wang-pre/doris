// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#pragma once

#include "common/status.h"
#include "vec/columns/column_map.h"
#include "vec/data_types/data_type.h"
#include "vec/data_types/data_type_array.h"
#include "vec/exprs/table_function/table_function.h"
#include "vec/functions/array/function_array_utils.h"

namespace doris::vectorized {

class VPosExplodeTableFunction : public TableFunction {
    ENABLE_FACTORY_CREATOR(VPosExplodeTableFunction);

public:
    VPosExplodeTableFunction();

    ~VPosExplodeTableFunction() override = default;

    Status process_init(Block* block, RuntimeState* state) override;
    void process_row(size_t row_idx) override;
    void process_close() override;
    void get_same_many_values(MutableColumnPtr& column, int length) override;
    int get_value(MutableColumnPtr& column, int max_step) override;

private:
    ColumnPtr _collection_column;
    ColumnPtr _array_data_column;
    ColumnArrayExecutionData _array_detail;
    size_t _collection_offset; // start offset of array[row_idx]
};

} // namespace doris::vectorized
