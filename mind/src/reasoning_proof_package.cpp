/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#include "petoron_ai/reasoning_proof_package.hpp"

namespace petoron_ai {

ReasoningProofPackage build_reasoning_proof_package(
    const ReasoningTransition& transition
) {
    ReasoningProofPackage package;
    package.trace = build_reasoning_trace(transition);
    package.input = build_reasoning_proof_input(package.trace);
    package.statement_id =
        commit_reasoning_proof_input(package.input);
    return package;
}

bool verify_reasoning_proof_package(
    const ReasoningProofPackage& package
) {
    if (!verify_reasoning_proof_input(
        package.trace,
        package.input
    )) {
        return false;
    }

    return package.statement_id ==
        commit_reasoning_proof_input(package.input);
}

}
