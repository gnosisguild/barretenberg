// AUTOGENERATED FILE
#pragma once

#include "barretenberg/commitment_schemes/kzg/kzg.hpp"
#include "barretenberg/ecc/curves/bn254/g1.hpp"
#include "barretenberg/flavor/relation_definitions.hpp"
#include "barretenberg/polynomials/barycentric.hpp"
#include "barretenberg/polynomials/univariate.hpp"

#include "barretenberg/flavor/flavor.hpp"
#include "barretenberg/flavor/flavor_macros.hpp"
#include "barretenberg/polynomials/evaluation_domain.hpp"
#include "barretenberg/transcript/transcript.hpp"

#include "barretenberg/vm/aztec_constants.hpp"
#include "barretenberg/vm2/common/macros.hpp"
#include "columns.hpp"
#include "flavor_settings.hpp"

// Relations
#include "relations/address_derivation.hpp"
#include "relations/alu.hpp"
#include "relations/bc_decomposition.hpp"
#include "relations/bc_hashing.hpp"
#include "relations/bc_retrieval.hpp"
#include "relations/bitwise.hpp"
#include "relations/class_id_derivation.hpp"
#include "relations/context.hpp"
#include "relations/context_stack.hpp"
#include "relations/ecc.hpp"
#include "relations/execution.hpp"
#include "relations/ff_gt.hpp"
#include "relations/instr_fetching.hpp"
#include "relations/merkle_check.hpp"
#include "relations/poseidon2_hash.hpp"
#include "relations/poseidon2_perm.hpp"
#include "relations/range_check.hpp"
#include "relations/scalar_mul.hpp"
#include "relations/sha256.hpp"
#include "relations/to_radix.hpp"

// Lookup and permutation relations
#include "relations/lookups_address_derivation.hpp"
#include "relations/lookups_bc_decomposition.hpp"
#include "relations/lookups_bc_hashing.hpp"
#include "relations/lookups_bc_retrieval.hpp"
#include "relations/lookups_bitwise.hpp"
#include "relations/lookups_class_id_derivation.hpp"
#include "relations/lookups_ff_gt.hpp"
#include "relations/lookups_instr_fetching.hpp"
#include "relations/lookups_merkle_check.hpp"
#include "relations/lookups_poseidon2_hash.hpp"
#include "relations/lookups_range_check.hpp"
#include "relations/lookups_scalar_mul.hpp"
#include "relations/lookups_sha256.hpp"
#include "relations/lookups_to_radix.hpp"

// Metaprogramming to concatenate tuple types.
template <typename... input_t> using tuple_cat_t = decltype(std::tuple_cat(std::declval<input_t>()...));

// clang-format off
// These getters are used to speedup logderivative inverses.
// See https://github.com/AztecProtocol/aztec-packages/pull/11605/ for a full explanation.
#define DEFAULT_GETTERS(ENTITY) \
    inline auto& _##ENTITY() { return ENTITY; } \
    inline auto& _##ENTITY() const { return ENTITY; }
#define ROW_PROXY_GETTERS(ENTITY) \
    inline auto& _##ENTITY() { return pp.ENTITY[row_idx]; } \
    inline auto& _##ENTITY() const { return pp.ENTITY[row_idx]; }
#define DEFINE_GETTERS(GETTER_MACRO, ENTITIES) \
    FOR_EACH(GETTER_MACRO, ENTITIES)
// clang-format on

namespace bb::avm2 {

class AvmFlavor {
  public:
    using Curve = AvmFlavorSettings::Curve;
    using G1 = AvmFlavorSettings::G1;
    using PCS = AvmFlavorSettings::PCS;

    using FF = AvmFlavorSettings::FF;
    using Polynomial = AvmFlavorSettings::Polynomial;
    using PolynomialHandle = AvmFlavorSettings::PolynomialHandle;
    using GroupElement = AvmFlavorSettings::GroupElement;
    using Commitment = AvmFlavorSettings::Commitment;
    using CommitmentHandle = AvmFlavorSettings::CommitmentHandle;
    using CommitmentKey = AvmFlavorSettings::CommitmentKey;
    using VerifierCommitmentKey = AvmFlavorSettings::VerifierCommitmentKey;
    using RelationSeparator = AvmFlavorSettings::RelationSeparator;

    // indicates when evaluating sumcheck, edges must be extended to be MAX_TOTAL_RELATION_LENGTH
    static constexpr bool USE_SHORT_MONOMIALS = false;

    // This flavor would not be used with ZK Sumcheck
    static constexpr bool HasZK = false;

    static constexpr size_t NUM_PRECOMPUTED_ENTITIES = 47;
    static constexpr size_t NUM_WITNESS_ENTITIES = 942;
    static constexpr size_t NUM_SHIFTED_ENTITIES = 135;
    static constexpr size_t NUM_WIRES = NUM_WITNESS_ENTITIES + NUM_PRECOMPUTED_ENTITIES;
    // We have two copies of the witness entities, so we subtract the number of fixed ones (they have no shift), one for
    // the unshifted and one for the shifted
    static constexpr size_t NUM_ALL_ENTITIES = 1124;

    // In the sumcheck univariate computation, we divide the trace in chunks and each chunk is
    // evenly processed by all the threads. This constant defines the maximum number of rows
    // that a given thread will process per chunk. This constant is assumed to be a power of 2
    // greater or equal to 2.
    // The current constant 32 is the result of time measurements using 16 threads and against
    // bulk test v2. It was performed at a stage where the trace was not large.
    // We note that all the experiments with constants below 256 did not exhibit any significant differences.
    // TODO: Fine-tune the following constant when avm is close to completion.
    static constexpr size_t MAX_CHUNK_THREAD_PORTION_SIZE = 32;

    // Need to be templated for recursive verifier
    template <typename FF_>
    using MainRelations_ = std::tuple<
        // Relations
        avm2::address_derivation<FF_>,
        avm2::alu<FF_>,
        avm2::bc_decomposition<FF_>,
        avm2::bc_hashing<FF_>,
        avm2::bc_retrieval<FF_>,
        avm2::bitwise<FF_>,
        avm2::class_id_derivation<FF_>,
        avm2::context<FF_>,
        avm2::context_stack<FF_>,
        avm2::ecc<FF_>,
        avm2::execution<FF_>,
        avm2::ff_gt<FF_>,
        avm2::instr_fetching<FF_>,
        avm2::merkle_check<FF_>,
        avm2::poseidon2_hash<FF_>,
        avm2::poseidon2_perm<FF_>,
        avm2::range_check<FF_>,
        avm2::scalar_mul<FF_>,
        avm2::sha256<FF_>,
        avm2::to_radix<FF_>>;

    using MainRelations = MainRelations_<FF>;

    // Need to be templated for recursive verifier
    template <typename FF_>
    using LookupRelations_ = std::tuple<
        // Lookups
        lookup_address_derivation_address_ecadd_relation<FF_>,
        lookup_address_derivation_partial_address_poseidon2_relation<FF_>,
        lookup_address_derivation_preaddress_poseidon2_relation<FF_>,
        lookup_address_derivation_preaddress_scalar_mul_relation<FF_>,
        lookup_address_derivation_public_keys_hash_poseidon2_0_relation<FF_>,
        lookup_address_derivation_public_keys_hash_poseidon2_1_relation<FF_>,
        lookup_address_derivation_public_keys_hash_poseidon2_2_relation<FF_>,
        lookup_address_derivation_public_keys_hash_poseidon2_3_relation<FF_>,
        lookup_address_derivation_public_keys_hash_poseidon2_4_relation<FF_>,
        lookup_address_derivation_salted_initialization_hash_poseidon2_0_relation<FF_>,
        lookup_address_derivation_salted_initialization_hash_poseidon2_1_relation<FF_>,
        lookup_bc_decomposition_abs_diff_is_u16_relation<FF_>,
        lookup_bc_decomposition_bytes_are_bytes_relation<FF_>,
        lookup_bc_decomposition_bytes_to_read_as_unary_relation<FF_>,
        lookup_bc_hashing_get_packed_field_relation<FF_>,
        lookup_bc_hashing_iv_is_len_relation<FF_>,
        lookup_bc_hashing_poseidon2_hash_relation<FF_>,
        lookup_bc_retrieval_bytecode_hash_is_correct_relation<FF_>,
        lookup_bc_retrieval_class_id_derivation_relation<FF_>,
        lookup_bitwise_byte_operations_relation<FF_>,
        lookup_bitwise_integral_tag_length_relation<FF_>,
        lookup_class_id_derivation_class_id_poseidon2_0_relation<FF_>,
        lookup_class_id_derivation_class_id_poseidon2_1_relation<FF_>,
        lookup_ff_gt_a_hi_range_relation<FF_>,
        lookup_ff_gt_a_lo_range_relation<FF_>,
        lookup_instr_fetching_bytecode_size_from_bc_dec_relation<FF_>,
        lookup_instr_fetching_bytes_from_bc_dec_relation<FF_>,
        lookup_instr_fetching_instr_abs_diff_positive_relation<FF_>,
        lookup_instr_fetching_pc_abs_diff_positive_relation<FF_>,
        lookup_instr_fetching_tag_value_validation_relation<FF_>,
        lookup_instr_fetching_wire_instruction_info_relation<FF_>,
        lookup_merkle_check_merkle_poseidon2_read_relation<FF_>,
        lookup_merkle_check_merkle_poseidon2_write_relation<FF_>,
        lookup_poseidon2_hash_poseidon2_perm_relation<FF_>,
        lookup_range_check_dyn_diff_is_u16_relation<FF_>,
        lookup_range_check_dyn_rng_chk_pow_2_relation<FF_>,
        lookup_range_check_r0_is_u16_relation<FF_>,
        lookup_range_check_r1_is_u16_relation<FF_>,
        lookup_range_check_r2_is_u16_relation<FF_>,
        lookup_range_check_r3_is_u16_relation<FF_>,
        lookup_range_check_r4_is_u16_relation<FF_>,
        lookup_range_check_r5_is_u16_relation<FF_>,
        lookup_range_check_r6_is_u16_relation<FF_>,
        lookup_range_check_r7_is_u16_relation<FF_>,
        lookup_scalar_mul_add_relation<FF_>,
        lookup_scalar_mul_double_relation<FF_>,
        lookup_scalar_mul_to_radix_relation<FF_>,
        lookup_sha256_round_constant_relation<FF_>,
        lookup_to_radix_fetch_p_limb_relation<FF_>,
        lookup_to_radix_fetch_safe_limbs_relation<FF_>,
        lookup_to_radix_limb_less_than_radix_range_relation<FF_>,
        lookup_to_radix_limb_p_diff_range_relation<FF_>,
        lookup_to_radix_limb_range_relation<FF_>>;

    using LookupRelations = LookupRelations_<FF>;

    // Need to be templated for recursive verifier
    template <typename FF_> using Relations_ = tuple_cat_t<MainRelations_<FF_>, LookupRelations_<FF_>>;
    using Relations = Relations_<FF>;

    static constexpr size_t MAX_PARTIAL_RELATION_LENGTH = compute_max_partial_relation_length<Relations>();

    // BATCHED_RELATION_PARTIAL_LENGTH = algebraic degree of sumcheck relation *after* multiplying by the `pow_zeta`
    // random polynomial e.g. For \sum(x) [A(x) * B(x) + C(x)] * PowZeta(X), relation length = 2 and random relation
    // length = 3
    static constexpr size_t BATCHED_RELATION_PARTIAL_LENGTH = MAX_PARTIAL_RELATION_LENGTH + 1;
    static constexpr size_t NUM_RELATIONS = std::tuple_size_v<Relations>;

    using SumcheckTupleOfTuplesOfUnivariates = decltype(create_sumcheck_tuple_of_tuples_of_univariates<Relations>());
    using TupleOfArraysOfValues = decltype(create_tuple_of_arrays_of_values<Relations>());

    static constexpr bool has_zero_row = true;

    static constexpr size_t NUM_FRS_COM = field_conversion::calc_num_bn254_frs<Commitment>();
    static constexpr size_t NUM_FRS_FR = field_conversion::calc_num_bn254_frs<FF>();

    // After any circuit changes, hover `COMPUTED_AVM_PROOF_LENGTH_IN_FIELDS` in your IDE
    // to see its value and then update `AVM_PROOF_LENGTH_IN_FIELDS` in constants.nr.
    static constexpr size_t COMPUTED_AVM_PROOF_LENGTH_IN_FIELDS =
        (NUM_WITNESS_ENTITIES + 1) * NUM_FRS_COM + (NUM_ALL_ENTITIES + 1) * NUM_FRS_FR +
        CONST_PROOF_SIZE_LOG_N * (NUM_FRS_COM + NUM_FRS_FR * (BATCHED_RELATION_PARTIAL_LENGTH + 1));

    template <typename DataType> class PrecomputedEntities {
      public:
        DEFINE_FLAVOR_MEMBERS(DataType, AVM2_PRECOMPUTED_ENTITIES)
        DEFINE_GETTERS(DEFAULT_GETTERS, AVM2_PRECOMPUTED_ENTITIES)
    };

  private:
    template <typename DataType> class WireEntities {
      public:
        DEFINE_FLAVOR_MEMBERS(DataType, AVM2_WIRE_ENTITIES)
        DEFINE_GETTERS(DEFAULT_GETTERS, AVM2_WIRE_ENTITIES)
    };

    template <typename DataType> class DerivedWitnessEntities {
      public:
        DEFINE_FLAVOR_MEMBERS(DataType, AVM2_DERIVED_WITNESS_ENTITIES)
        DEFINE_GETTERS(DEFAULT_GETTERS, AVM2_DERIVED_WITNESS_ENTITIES)
    };

    template <typename DataType> class ShiftedEntities {
      public:
        DEFINE_FLAVOR_MEMBERS(DataType, AVM2_SHIFTED_ENTITIES)
        DEFINE_GETTERS(DEFAULT_GETTERS, AVM2_SHIFTED_ENTITIES)
    };

    template <typename DataType, typename PrecomputedAndWitnessEntitiesSuperset>
    static auto get_to_be_shifted([[maybe_unused]] PrecomputedAndWitnessEntitiesSuperset& entities)
    {
        return RefArray<DataType, NUM_SHIFTED_ENTITIES>{ AVM2_TO_BE_SHIFTED(entities) };
    }

  public:
    template <typename DataType>
    class WitnessEntities : public WireEntities<DataType>, public DerivedWitnessEntities<DataType> {
      public:
        DEFINE_COMPOUND_GET_ALL(WireEntities<DataType>, DerivedWitnessEntities<DataType>)
        auto get_wires() { return WireEntities<DataType>::get_all(); }
        static const auto& get_wires_labels() { return WireEntities<DataType>::get_labels(); }
        auto get_derived() { return DerivedWitnessEntities<DataType>::get_all(); }
        static const auto& get_derived_labels() { return DerivedWitnessEntities<DataType>::get_labels(); }
    };

    template <typename DataType>
    class AllEntities : public PrecomputedEntities<DataType>,
                        public WitnessEntities<DataType>,
                        public ShiftedEntities<DataType> {
      public:
        DEFINE_COMPOUND_GET_ALL(PrecomputedEntities<DataType>, WitnessEntities<DataType>, ShiftedEntities<DataType>)

        auto get_unshifted()
        {
            return concatenate(PrecomputedEntities<DataType>::get_all(), WitnessEntities<DataType>::get_all());
        }

        static const auto& get_unshifted_labels()
        {
            static const auto labels =
                concatenate(PrecomputedEntities<DataType>::get_labels(), WitnessEntities<DataType>::get_labels());
            return labels;
        }

        auto get_to_be_shifted() { return AvmFlavor::get_to_be_shifted<DataType>(*this); }
        auto get_shifted() { return ShiftedEntities<DataType>::get_all(); }
        auto get_precomputed() { return PrecomputedEntities<DataType>::get_all(); }
    };

    class ProvingKey : public PrecomputedEntities<Polynomial>, public WitnessEntities<Polynomial> {
      public:
        using FF = typename Polynomial::FF;
        DEFINE_COMPOUND_GET_ALL(PrecomputedEntities<Polynomial>, WitnessEntities<Polynomial>);

        ProvingKey() = default;
        ProvingKey(const size_t circuit_size, const size_t num_public_inputs);

        size_t circuit_size;
        size_t log_circuit_size;
        size_t num_public_inputs;
        bb::EvaluationDomain<FF> evaluation_domain;
        std::shared_ptr<CommitmentKey> commitment_key;

        // Offset off the public inputs from the start of the execution trace
        size_t pub_inputs_offset = 0;

        // The number of public inputs has to be the same for all instances because they are
        // folded element by element.
        std::vector<FF> public_inputs;

        auto get_witness_polynomials() { return WitnessEntities<Polynomial>::get_all(); }
        auto get_precomputed_polynomials() { return PrecomputedEntities<Polynomial>::get_all(); }
        auto get_selectors() { return PrecomputedEntities<Polynomial>::get_all(); }
        auto get_to_be_shifted() { return AvmFlavor::get_to_be_shifted<Polynomial>(*this); }
    };

    class VerificationKey : public VerificationKey_<uint64_t, PrecomputedEntities<Commitment>, VerifierCommitmentKey> {
      public:
        using FF = VerificationKey_::FF;
        static constexpr size_t NUM_PRECOMPUTED_COMMITMENTS = NUM_PRECOMPUTED_ENTITIES;

        VerificationKey() = default;

        VerificationKey(const std::shared_ptr<ProvingKey>& proving_key)
            : VerificationKey_(proving_key->circuit_size, static_cast<size_t>(proving_key->num_public_inputs))
        {
            for (auto [polynomial, commitment] :
                 zip_view(proving_key->get_precomputed_polynomials(), this->get_all())) {
                commitment = proving_key->commitment_key->commit(polynomial);
            }
            pcs_verification_key = std::make_shared<VerifierCommitmentKey>();
        }

        VerificationKey(const size_t circuit_size,
                        const size_t num_public_inputs,
                        std::array<Commitment, NUM_PRECOMPUTED_COMMITMENTS> const& precomputed_cmts)
            : VerificationKey_(circuit_size, num_public_inputs)
        {
            for (auto [vk_cmt, cmt] : zip_view(this->get_all(), precomputed_cmts)) {
                vk_cmt = cmt;
            }
            pcs_verification_key = std::make_shared<VerifierCommitmentKey>();
        }

        std::vector<FF> to_field_elements() const;
    };

    class AllValues : public AllEntities<FF> {
      public:
        using Base = AllEntities<FF>;
        using Base::Base;
    };

    // Only used by VM1 check_circuit. Remove.
    class AllConstRefValues {
      public:
        using BaseDataType = const FF;
        using DataType = BaseDataType&;
        DEFINE_FLAVOR_MEMBERS(DataType, AVM2_ALL_ENTITIES)
        DEFINE_GETTERS(DEFAULT_GETTERS, AVM2_ALL_ENTITIES)
    };

    template <typename Polynomials> class PolynomialEntitiesAtFixedRow {
      public:
        PolynomialEntitiesAtFixedRow(const size_t row_idx, const Polynomials& pp)
            : row_idx(row_idx)
            , pp(pp)
        {}
        DEFINE_GETTERS(ROW_PROXY_GETTERS, AVM2_ALL_ENTITIES)

      private:
        const size_t row_idx;
        const Polynomials& pp;
    };

    /**
     * @brief A container for the prover polynomials handles.
     */
    class ProverPolynomials : public AllEntities<Polynomial> {
      public:
        // Define all operations as default, except copy construction/assignment
        ProverPolynomials() = default;
        ProverPolynomials& operator=(const ProverPolynomials&) = delete;
        ProverPolynomials(const ProverPolynomials& o) = delete;
        ProverPolynomials(ProverPolynomials&& o) noexcept = default;
        ProverPolynomials& operator=(ProverPolynomials&& o) noexcept = default;
        ~ProverPolynomials() = default;

        ProverPolynomials(ProvingKey& proving_key);

        size_t get_polynomial_size() const { return execution_input.size(); }
        // This is only used in VM1 check_circuit. Remove.
        AllConstRefValues get_standard_row(size_t row_idx) const
        {
            return [row_idx](auto&... entities) -> AllConstRefValues {
                return { entities[row_idx]... };
            }(AVM2_ALL_ENTITIES);
        }
        auto get_row(size_t row_idx) const { return PolynomialEntitiesAtFixedRow<ProverPolynomials>(row_idx, *this); }
    };

    class PartiallyEvaluatedMultivariates : public AllEntities<Polynomial> {
      public:
        PartiallyEvaluatedMultivariates() = default;
        PartiallyEvaluatedMultivariates(const size_t circuit_size);
        PartiallyEvaluatedMultivariates(const ProverPolynomials& full_polynomials, size_t circuit_size);
    };

    /**
     * @brief A container for univariates used during Protogalaxy folding and sumcheck.
     * @details During folding and sumcheck, the prover evaluates the relations on these univariates.
     */
    template <size_t LENGTH> using ProverUnivariates = AllEntities<bb::Univariate<FF, LENGTH>>;

    /**
     * @brief A container for univariates used during Protogalaxy folding and sumcheck with some of the computation
     * optimistically ignored
     * @details During folding and sumcheck, the prover evaluates the relations on these univariates.
     */
    template <size_t LENGTH, size_t SKIP_COUNT>
    using ProverUnivariatesWithOptimisticSkipping = AllEntities<bb::Univariate<FF, LENGTH, 0, SKIP_COUNT>>;

    /**
     * @brief A container for univariates produced during the hot loop in sumcheck.
     */
    using ExtendedEdges = ProverUnivariates<MAX_PARTIAL_RELATION_LENGTH>;

    /**
     * @brief A container for the witness commitments.
     *
     */
    using WitnessCommitments = WitnessEntities<Commitment>;

    // Templated for use in recursive verifier
    template <typename Commitment_, typename VerificationKey>
    class VerifierCommitments_ : public AllEntities<Commitment_> {
      private:
        using Base = AllEntities<Commitment_>;

      public:
        VerifierCommitments_(const std::shared_ptr<VerificationKey>& verification_key)
        {
            for (auto [commitment, vk_commitment] : zip_view(this->get_precomputed(), verification_key->get_all())) {
                commitment = vk_commitment;
            }
        }
    };

    // Native version of the verifier commitments
    using VerifierCommitments = VerifierCommitments_<Commitment, VerificationKey>;

    class Transcript : public NativeTranscript {
      public:
        uint32_t circuit_size;

        std::array<Commitment, NUM_WITNESS_ENTITIES> commitments;

        std::vector<bb::Univariate<FF, BATCHED_RELATION_PARTIAL_LENGTH>> sumcheck_univariates;
        std::array<FF, NUM_ALL_ENTITIES> sumcheck_evaluations;
        std::vector<Commitment> gemini_fold_comms;
        std::vector<FF> gemini_fold_evals;
        Commitment shplonk_q_comm;
        Commitment kzg_w_comm;

        Transcript() = default;

        Transcript(const std::vector<FF>& proof)
            : NativeTranscript(proof)
        {}

        void deserialize_full_transcript();
        void serialize_full_transcript();
    };
};

} // namespace bb::avm2
