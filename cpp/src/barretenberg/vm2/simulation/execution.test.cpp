#include "barretenberg/vm2/simulation/execution.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>

#include "barretenberg/vm2/common/field.hpp"
#include "barretenberg/vm2/common/memory_types.hpp"
#include "barretenberg/vm2/common/opcodes.hpp"
#include "barretenberg/vm2/simulation/context.hpp"
#include "barretenberg/vm2/simulation/events/event_emitter.hpp"
#include "barretenberg/vm2/simulation/events/execution_event.hpp"
#include "barretenberg/vm2/simulation/lib/instruction_info.hpp"
#include "barretenberg/vm2/simulation/lib/serialization.hpp"
#include "barretenberg/vm2/simulation/memory.hpp"
#include "barretenberg/vm2/simulation/testing/mock_alu.hpp"
#include "barretenberg/vm2/simulation/testing/mock_bytecode_manager.hpp"
#include "barretenberg/vm2/simulation/testing/mock_context.hpp"
#include "barretenberg/vm2/simulation/testing/mock_execution_components.hpp"
#include "barretenberg/vm2/simulation/testing/mock_memory.hpp"

namespace bb::avm2::simulation {
namespace {

using ::testing::_;
using ::testing::Ref;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::StrictMock;

class ExecutionSimulationTest : public ::testing::Test {
  protected:
    ExecutionSimulationTest() { ON_CALL(context, get_memory).WillByDefault(ReturnRef(memory)); }

    StrictMock<MockAlu> alu;
    StrictMock<MockMemory> memory;
    StrictMock<MockExecutionComponentsProvider> execution_components;
    StrictMock<MockContext> context;
    EventEmitter<ExecutionEvent> execution_event_emitter;
    EventEmitter<ContextStackEvent> context_stack_event_emitter;
    InstructionInfoDB instruction_info_db; // Using the real thing.
    Execution execution =
        Execution(alu, execution_components, instruction_info_db, execution_event_emitter, context_stack_event_emitter);
};

TEST_F(ExecutionSimulationTest, Add)
{
    ValueRefAndTag a = { .value = 4, .tag = MemoryTag::U32 };
    ValueRefAndTag b = { .value = 5, .tag = MemoryTag::U32 };

    EXPECT_CALL(context, get_memory);
    EXPECT_CALL(memory, get).Times(2).WillOnce(Return(a)).WillOnce(Return(b));
    EXPECT_CALL(alu, add(a, b)).WillOnce(Return(9));
    EXPECT_CALL(memory, set(6, FF(9), MemoryTag::U32));
    execution.add(context, 4, 5, 6);
}

TEST_F(ExecutionSimulationTest, Call)
{

    AztecAddress parent_address = 1;
    AztecAddress nested_address = 2;

    // Context snapshotting
    EXPECT_CALL(context, get_context_id);
    EXPECT_CALL(context, get_next_pc);
    EXPECT_CALL(context, get_is_static);
    EXPECT_CALL(context, get_msg_sender).WillOnce(ReturnRef(parent_address));

    EXPECT_CALL(context, get_memory);
    EXPECT_CALL(context, get_address).WillRepeatedly(ReturnRef(parent_address));
    EXPECT_CALL(memory, get).WillOnce(Return(ValueRefAndTag({ .value = nested_address, .tag = MemoryTag::U32 })));

    EXPECT_CALL(execution_components, make_nested_context(nested_address, parent_address, _, _, _, _))
        .WillOnce(Return(std::make_unique<MockContext>()));

    EXPECT_CALL(context, set_child_context(_));
    EXPECT_CALL(context, set_last_rd_offset(_));
    EXPECT_CALL(context, set_last_rd_size(_));
    EXPECT_CALL(context, set_last_success(_));

    execution.call(context, 10, 20, 30);
}

} // namespace
} // namespace bb::avm2::simulation
