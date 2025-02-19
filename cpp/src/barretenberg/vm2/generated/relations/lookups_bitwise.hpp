// AUTOGENERATED FILE
#pragma once

#include "../columns.hpp"
#include "barretenberg/relations/generic_lookup/generic_lookup_relation.hpp"

#include <cstddef>
#include <string_view>
#include <tuple>

namespace bb::avm2 {

/////////////////// lookup_bitw_byte_lengths ///////////////////

class lookup_bitw_byte_lengths_lookup_settings {
  public:
    static constexpr std::string_view NAME = "LOOKUP_BITW_BYTE_LENGTHS";
    static constexpr std::string_view RELATION_NAME = "bitwise";

    static constexpr size_t READ_TERMS = 1;
    static constexpr size_t WRITE_TERMS = 1;
    static constexpr size_t READ_TERM_TYPES[READ_TERMS] = { 0 };
    static constexpr size_t WRITE_TERM_TYPES[WRITE_TERMS] = { 0 };
    static constexpr size_t LOOKUP_TUPLE_SIZE = 2;
    static constexpr size_t INVERSE_EXISTS_POLYNOMIAL_DEGREE = 4;
    static constexpr size_t READ_TERM_DEGREE = 0;
    static constexpr size_t WRITE_TERM_DEGREE = 0;

    // Columns using the Column enum.
    static constexpr Column SRC_SELECTOR = Column::bitwise_start;
    static constexpr Column DST_SELECTOR = Column::precomputed_sel_integral_tag;
    static constexpr Column COUNTS = Column::lookup_bitw_byte_lengths_counts;
    static constexpr Column INVERSES = Column::lookup_bitw_byte_lengths_inv;
    static constexpr std::array<Column, LOOKUP_TUPLE_SIZE> SRC_COLUMNS = { Column::bitwise_tag, Column::bitwise_ctr };
    static constexpr std::array<Column, LOOKUP_TUPLE_SIZE> DST_COLUMNS = { Column::precomputed_clk,
                                                                           Column::precomputed_integral_tag_length };

    template <typename AllEntities> static inline auto inverse_polynomial_is_computed_at_row(const AllEntities& in)
    {
        return (in._bitwise_start() == 1 || in._precomputed_sel_integral_tag() == 1);
    }

    template <typename Accumulator, typename AllEntities>
    static inline auto compute_inverse_exists(const AllEntities& in)
    {
        using View = typename Accumulator::View;
        const auto is_operation = View(in._bitwise_start());
        const auto is_table_entry = View(in._precomputed_sel_integral_tag());
        return (is_operation + is_table_entry - is_operation * is_table_entry);
    }

    template <typename AllEntities> static inline auto get_const_entities(const AllEntities& in)
    {
        return get_entities(in);
    }

    template <typename AllEntities> static inline auto get_nonconst_entities(AllEntities& in)
    {
        return get_entities(in);
    }

    template <typename AllEntities> static inline auto get_entities(AllEntities&& in)
    {
        return std::forward_as_tuple(in._lookup_bitw_byte_lengths_inv(),
                                     in._lookup_bitw_byte_lengths_counts(),
                                     in._bitwise_start(),
                                     in._precomputed_sel_integral_tag(),
                                     in._bitwise_tag(),
                                     in._bitwise_ctr(),
                                     in._precomputed_clk(),
                                     in._precomputed_integral_tag_length());
    }
};

template <typename FF_>
class lookup_bitw_byte_lengths_relation : public GenericLookupRelation<lookup_bitw_byte_lengths_lookup_settings, FF_> {
  public:
    using Settings = lookup_bitw_byte_lengths_lookup_settings;
    static constexpr std::string_view NAME = lookup_bitw_byte_lengths_lookup_settings::NAME;
    static constexpr std::string_view RELATION_NAME = lookup_bitw_byte_lengths_lookup_settings::RELATION_NAME;

    template <typename AllEntities> inline static bool skip(const AllEntities& in)
    {
        return in.lookup_bitw_byte_lengths_inv.is_zero();
    }

    static std::string get_subrelation_label(size_t index)
    {
        if (index == 0) {
            return "INVERSES_ARE_CORRECT";
        } else if (index == 1) {
            return "ACCUMULATION_IS_CORRECT";
        }
        return std::to_string(index);
    }
};

/////////////////// lookup_bitw_byte_operations ///////////////////

class lookup_bitw_byte_operations_lookup_settings {
  public:
    static constexpr std::string_view NAME = "LOOKUP_BITW_BYTE_OPERATIONS";
    static constexpr std::string_view RELATION_NAME = "bitwise";

    static constexpr size_t READ_TERMS = 1;
    static constexpr size_t WRITE_TERMS = 1;
    static constexpr size_t READ_TERM_TYPES[READ_TERMS] = { 0 };
    static constexpr size_t WRITE_TERM_TYPES[WRITE_TERMS] = { 0 };
    static constexpr size_t LOOKUP_TUPLE_SIZE = 4;
    static constexpr size_t INVERSE_EXISTS_POLYNOMIAL_DEGREE = 4;
    static constexpr size_t READ_TERM_DEGREE = 0;
    static constexpr size_t WRITE_TERM_DEGREE = 0;

    // Columns using the Column enum.
    static constexpr Column SRC_SELECTOR = Column::bitwise_sel;
    static constexpr Column DST_SELECTOR = Column::precomputed_sel_bitwise;
    static constexpr Column COUNTS = Column::lookup_bitw_byte_operations_counts;
    static constexpr Column INVERSES = Column::lookup_bitw_byte_operations_inv;
    static constexpr std::array<Column, LOOKUP_TUPLE_SIZE> SRC_COLUMNS = {
        Column::bitwise_op_id, Column::bitwise_ia_byte, Column::bitwise_ib_byte, Column::bitwise_ic_byte
    };
    static constexpr std::array<Column, LOOKUP_TUPLE_SIZE> DST_COLUMNS = { Column::precomputed_bitwise_op_id,
                                                                           Column::precomputed_bitwise_input_a,
                                                                           Column::precomputed_bitwise_input_b,
                                                                           Column::precomputed_bitwise_output };

    template <typename AllEntities> static inline auto inverse_polynomial_is_computed_at_row(const AllEntities& in)
    {
        return (in._bitwise_sel() == 1 || in._precomputed_sel_bitwise() == 1);
    }

    template <typename Accumulator, typename AllEntities>
    static inline auto compute_inverse_exists(const AllEntities& in)
    {
        using View = typename Accumulator::View;
        const auto is_operation = View(in._bitwise_sel());
        const auto is_table_entry = View(in._precomputed_sel_bitwise());
        return (is_operation + is_table_entry - is_operation * is_table_entry);
    }

    template <typename AllEntities> static inline auto get_const_entities(const AllEntities& in)
    {
        return get_entities(in);
    }

    template <typename AllEntities> static inline auto get_nonconst_entities(AllEntities& in)
    {
        return get_entities(in);
    }

    template <typename AllEntities> static inline auto get_entities(AllEntities&& in)
    {
        return std::forward_as_tuple(in._lookup_bitw_byte_operations_inv(),
                                     in._lookup_bitw_byte_operations_counts(),
                                     in._bitwise_sel(),
                                     in._precomputed_sel_bitwise(),
                                     in._bitwise_op_id(),
                                     in._bitwise_ia_byte(),
                                     in._bitwise_ib_byte(),
                                     in._bitwise_ic_byte(),
                                     in._precomputed_bitwise_op_id(),
                                     in._precomputed_bitwise_input_a(),
                                     in._precomputed_bitwise_input_b(),
                                     in._precomputed_bitwise_output());
    }
};

template <typename FF_>
class lookup_bitw_byte_operations_relation
    : public GenericLookupRelation<lookup_bitw_byte_operations_lookup_settings, FF_> {
  public:
    using Settings = lookup_bitw_byte_operations_lookup_settings;
    static constexpr std::string_view NAME = lookup_bitw_byte_operations_lookup_settings::NAME;
    static constexpr std::string_view RELATION_NAME = lookup_bitw_byte_operations_lookup_settings::RELATION_NAME;

    template <typename AllEntities> inline static bool skip(const AllEntities& in)
    {
        return in.lookup_bitw_byte_operations_inv.is_zero();
    }

    static std::string get_subrelation_label(size_t index)
    {
        if (index == 0) {
            return "INVERSES_ARE_CORRECT";
        } else if (index == 1) {
            return "ACCUMULATION_IS_CORRECT";
        }
        return std::to_string(index);
    }
};

} // namespace bb::avm2
