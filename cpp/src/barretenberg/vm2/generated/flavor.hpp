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
#include "columns.hpp"
#include "flavor_settings.hpp"

// Relations
#include "relations/alu.hpp"
#include "relations/execution.hpp"
#include "relations/range_check.hpp"

// Lookup and permutation relations
#include "relations/lookups_execution.hpp"
#include "relations/lookups_range_check.hpp"
#include "relations/perms_execution.hpp"

// Metaprogramming to concatenate tuple types.
template <typename... input_t> using tuple_cat_t = decltype(std::tuple_cat(std::declval<input_t>()...));

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

    static constexpr size_t NUM_PRECOMPUTED_ENTITIES = 10;
    static constexpr size_t NUM_WITNESS_ENTITIES = 91;
    static constexpr size_t NUM_SHIFTED_ENTITIES = 1;
    static constexpr size_t NUM_WIRES = NUM_WITNESS_ENTITIES + NUM_PRECOMPUTED_ENTITIES;
    // We have two copies of the witness entities, so we subtract the number of fixed ones (they have no shift), one for
    // the unshifted and one for the shifted
    static constexpr size_t NUM_ALL_ENTITIES = 102;
    // The total number of witnesses including shifts and derived entities.
    static constexpr size_t NUM_ALL_WITNESS_ENTITIES = NUM_WITNESS_ENTITIES + NUM_SHIFTED_ENTITIES;

    // Need to be templated for recursive verifier
    template <typename FF_>
    using MainRelations_ = std::tuple<
        // Relations
        avm2::alu<FF_>,
        avm2::execution<FF_>,
        avm2::range_check<FF_>>;

    using MainRelations = MainRelations_<FF>;

    // Need to be templated for recursive verifier
    template <typename FF_>
    using LookupRelations_ = std::tuple<
        // Lookups
        lookup_dummy_dynamic_relation<FF_>,
        lookup_dummy_precomputed_relation<FF_>,
        lookup_rng_chk_diff_relation<FF_>,
        lookup_rng_chk_is_r0_16_bit_relation<FF_>,
        lookup_rng_chk_is_r1_16_bit_relation<FF_>,
        lookup_rng_chk_is_r2_16_bit_relation<FF_>,
        lookup_rng_chk_is_r3_16_bit_relation<FF_>,
        lookup_rng_chk_is_r4_16_bit_relation<FF_>,
        lookup_rng_chk_is_r5_16_bit_relation<FF_>,
        lookup_rng_chk_is_r6_16_bit_relation<FF_>,
        lookup_rng_chk_is_r7_16_bit_relation<FF_>,
        lookup_rng_chk_pow_2_relation<FF_>,
        perm_dummy_dynamic_relation<FF_>>;

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

    template <typename DataType_> class PrecomputedEntities : public PrecomputedEntitiesBase {
      public:
        using DataType = DataType_;

        DEFINE_FLAVOR_MEMBERS(DataType, AVM2_PRECOMPUTED_ENTITIES)

        RefVector<DataType> get_selectors() { return get_all(); }
        RefVector<DataType> get_sigma_polynomials() { return {}; }
        RefVector<DataType> get_id_polynomials() { return {}; }
        RefVector<DataType> get_table_polynomials() { return {}; }
    };

  private:
    template <typename DataType> class WireEntities {
      public:
        DEFINE_FLAVOR_MEMBERS(DataType, AVM2_WIRE_ENTITIES)
    };

    template <typename DataType> class DerivedWitnessEntities {
      public:
        DEFINE_FLAVOR_MEMBERS(DataType, AVM2_DERIVED_WITNESS_ENTITIES)
    };

    template <typename DataType> class ShiftedEntities {
      public:
        DEFINE_FLAVOR_MEMBERS(DataType, AVM2_SHIFTED_ENTITIES)
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
        auto get_wires_labels() { return WireEntities<DataType>::get_labels(); }
        auto get_derived() { return DerivedWitnessEntities<DataType>::get_all(); }
        auto get_derived_labels() { return DerivedWitnessEntities<DataType>::get_labels(); }
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

        auto get_unshifted_labels()
        {
            return concatenate(PrecomputedEntities<DataType>::get_labels(), WitnessEntities<DataType>::get_labels());
        }

        auto get_to_be_shifted() { return AvmFlavor::get_to_be_shifted<DataType>(*this); }
        auto get_shifted() { return ShiftedEntities<DataType>::get_all(); }
        auto get_precomputed() { return PrecomputedEntities<DataType>::get_all(); }
    };

    class ProvingKey : public PrecomputedEntities<Polynomial>, public WitnessEntities<Polynomial> {
      public:
        using FF = typename Polynomial::FF;

        ProvingKey() = default;
        ProvingKey(const size_t circuit_size, const size_t num_public_inputs);

        size_t circuit_size;
        bb::EvaluationDomain<FF> evaluation_domain;
        std::shared_ptr<CommitmentKey> commitment_key;

        // Offset off the public inputs from the start of the execution trace
        size_t pub_inputs_offset = 0;

        // The number of public inputs has to be the same for all instances because they are
        // folded element by element.
        std::vector<FF> public_inputs;

        std::vector<std::string> get_labels() const
        {
            return concatenate(PrecomputedEntities<Polynomial>::get_labels(),
                               WitnessEntities<Polynomial>::get_labels());
        }
        auto get_witness_polynomials() { return WitnessEntities<Polynomial>::get_all(); }
        auto get_precomputed_polynomials() { return PrecomputedEntities<Polynomial>::get_all(); }
        auto get_selectors() { return PrecomputedEntities<Polynomial>::get_all(); }
        auto get_to_be_shifted() { return AvmFlavor::get_to_be_shifted<Polynomial>(*this); }
        // This order matters! must match get_unshifted in entity classes
        auto get_all() { return concatenate(get_precomputed_polynomials(), get_witness_polynomials()); }
    };

    class VerificationKey : public VerificationKey_<PrecomputedEntities<Commitment>, VerifierCommitmentKey> {
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

    class AllConstRefValues {
      public:
        using BaseDataType = const FF;
        using DataType = BaseDataType&;

        DEFINE_FLAVOR_MEMBERS(DataType, AVM2_ALL_ENTITIES)
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
        AllConstRefValues get_row(size_t row_idx) const
        {
            return [row_idx](auto&... entities) -> AllConstRefValues {
                return { entities[row_idx]... };
            }(AVM2_ALL_ENTITIES);
        }
    };

    class PartiallyEvaluatedMultivariates : public AllEntities<Polynomial> {
      public:
        PartiallyEvaluatedMultivariates() = default;
        PartiallyEvaluatedMultivariates(const size_t circuit_size);
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
            this->precomputed_bitwise_input_a = verification_key->precomputed_bitwise_input_a;
            this->precomputed_bitwise_input_b = verification_key->precomputed_bitwise_input_b;
            this->precomputed_bitwise_op_id = verification_key->precomputed_bitwise_op_id;
            this->precomputed_bitwise_output = verification_key->precomputed_bitwise_output;
            this->precomputed_clk = verification_key->precomputed_clk;
            this->precomputed_first_row = verification_key->precomputed_first_row;
            this->precomputed_power_of_2 = verification_key->precomputed_power_of_2;
            this->precomputed_sel_bitwise = verification_key->precomputed_sel_bitwise;
            this->precomputed_sel_range_16 = verification_key->precomputed_sel_range_16;
            this->precomputed_sel_range_8 = verification_key->precomputed_sel_range_8;
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
