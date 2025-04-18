#pragma once

#include <optional>

#include "barretenberg/crypto/merkle_tree/hash_path.hpp"
#include "barretenberg/crypto/merkle_tree/indexed_tree/indexed_leaf.hpp"
#include "barretenberg/crypto/merkle_tree/response.hpp"
#include "barretenberg/crypto/merkle_tree/types.hpp"
#include "barretenberg/vm2/common/avm_inputs.hpp"
#include "barretenberg/vm2/common/aztec_types.hpp"
#include "barretenberg/world_state/types.hpp"
#include "barretenberg/world_state/world_state.hpp"

namespace bb::avm2::simulation {

class ContractDBInterface {
  public:
    virtual ~ContractDBInterface() = default;

    virtual std::optional<ContractInstance> get_contract_instance(const AztecAddress& address) const = 0;
    virtual std::optional<ContractClass> get_contract_class(const ContractClassId& class_id) const = 0;
};

// Low level access to a merkle db. In general these will not be constrained.
class LowLevelMerkleDBInterface {
  public:
    virtual ~LowLevelMerkleDBInterface() = default;

    virtual const TreeSnapshots& get_tree_roots() const = 0;

    virtual crypto::merkle_tree::fr_sibling_path get_sibling_path(world_state::MerkleTreeId tree_id,
                                                                  crypto::merkle_tree::index_t leaf_index) const = 0;
    virtual crypto::merkle_tree::GetLowIndexedLeafResponse get_low_indexed_leaf(world_state::MerkleTreeId tree_id,
                                                                                const FF& value) const = 0;
    // Returns the value if it exists, 0 otherwise.
    virtual FF get_leaf_value(world_state::MerkleTreeId tree_id, crypto::merkle_tree::index_t leaf_index) const = 0;
    // We don't template the preimage methods because templated methods cannot be virtual.
    virtual crypto::merkle_tree::IndexedLeaf<crypto::merkle_tree::PublicDataLeafValue>
    get_leaf_preimage_public_data_tree(crypto::merkle_tree::index_t leaf_index) const = 0;
    virtual crypto::merkle_tree::IndexedLeaf<crypto::merkle_tree::NullifierLeafValue> get_leaf_preimage_nullifier_tree(
        crypto::merkle_tree::index_t leaf_index) const = 0;

    // Inserts a leaf into the public data tree sequentially, getting witnesses at every step.
    // Note: This method doesn't support inserting empty leaves.
    virtual world_state::SequentialInsertionResult<crypto::merkle_tree::PublicDataLeafValue>
    insert_indexed_leaves_public_data_tree(const crypto::merkle_tree::PublicDataLeafValue& leaf_value) = 0;

    // Inserts a leaf into the nullifier tree sequentially, getting witnesses at every step.
    // Note: This method doesn't support inserting empty leaves.
    virtual world_state::SequentialInsertionResult<crypto::merkle_tree::NullifierLeafValue>
    insert_indexed_leaves_nullifier_tree(const crypto::merkle_tree::NullifierLeafValue& leaf_value) = 0;
};

// High level access to a merkle db. In general these will be constrained.
class HighLevelMerkleDBInterface {
  public:
    virtual ~HighLevelMerkleDBInterface() = default;

    virtual const TreeSnapshots& get_tree_roots() const = 0;
    virtual FF storage_read(const FF& key) const = 0;
};

} // namespace bb::avm2::simulation
