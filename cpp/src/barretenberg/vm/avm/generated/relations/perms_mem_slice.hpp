// AUTOGENERATED FILE
#pragma once

#include "../columns.hpp"
#include "barretenberg/relations/generic_permutation/generic_permutation_relation.hpp"

#include <cstddef>
#include <string_view>
#include <tuple>

namespace bb::avm {

/////////////////// perm_slice_mem ///////////////////

class perm_slice_mem_permutation_settings {
  public:
    // This constant defines how many columns are bundled together to form each set.
    constexpr static size_t COLUMNS_PER_SET = 5;

    // Columns using the Column enum.
    static constexpr Column SRC_SELECTOR = Column::slice_sel_mem_active;
    static constexpr Column DST_SELECTOR = Column::mem_sel_op_slice;
    static constexpr Column INVERSES = Column::perm_slice_mem_inv;

    template <typename AllEntities> static inline auto inverse_polynomial_is_computed_at_row(const AllEntities& in)
    {
        return (in._slice_sel_mem_active() == 1 || in._mem_sel_op_slice() == 1);
    }

    template <typename AllEntities> static inline auto get_const_entities(const AllEntities& in)
    {
        return std::forward_as_tuple(in._perm_slice_mem_inv(),
                                     in._slice_sel_mem_active(),
                                     in._slice_sel_mem_active(),
                                     in._mem_sel_op_slice(),
                                     in._slice_clk(),
                                     in._slice_space_id(),
                                     in._slice_addr(),
                                     in._slice_val(),
                                     in._slice_sel_cd_cpy(),
                                     in._mem_clk(),
                                     in._mem_space_id(),
                                     in._mem_addr(),
                                     in._mem_val(),
                                     in._mem_rw());
    }

    template <typename AllEntities> static inline auto get_nonconst_entities(AllEntities& in)
    {
        return std::forward_as_tuple(in._perm_slice_mem_inv(),
                                     in._slice_sel_mem_active(),
                                     in._slice_sel_mem_active(),
                                     in._mem_sel_op_slice(),
                                     in._slice_clk(),
                                     in._slice_space_id(),
                                     in._slice_addr(),
                                     in._slice_val(),
                                     in._slice_sel_cd_cpy(),
                                     in._mem_clk(),
                                     in._mem_space_id(),
                                     in._mem_addr(),
                                     in._mem_val(),
                                     in._mem_rw());
    }
};

template <typename FF_>
class perm_slice_mem_relation : public GenericPermutationRelation<perm_slice_mem_permutation_settings, FF_> {
  public:
    static constexpr std::string_view NAME = "PERM_SLICE_MEM";
};
template <typename FF_> using perm_slice_mem = GenericPermutation<perm_slice_mem_permutation_settings, FF_>;

} // namespace bb::avm