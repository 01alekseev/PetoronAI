/*
Copyright (c) Ivan Alekseev

Licensed under the PetoronAI Community License (PCL)
or a valid PetoronAI Commercial License.
*/

#pragma once

#include <atomic>
#include <chrono>

namespace butler_hands {

class ExecutionContext final {
public:
    using Clock = std::chrono::steady_clock;

    ExecutionContext(
        const std::atomic_bool& cancelled,
        std::chrono::milliseconds timeout
    )
        : cancelled_(cancelled),
          has_deadline_(timeout.count() > 0),
          deadline_(
              has_deadline_
                  ? Clock::now() + timeout
                  : Clock::time_point::max()
          ) {}

    [[nodiscard]]
    bool cancellation_requested() const noexcept {
        return cancelled_.load(std::memory_order_relaxed);
    }

    [[nodiscard]]
    bool deadline_exceeded() const noexcept {
        return has_deadline_ &&
               Clock::now() >= deadline_;
    }

    [[nodiscard]]
    bool stop_requested() const noexcept {
        return cancellation_requested() ||
               deadline_exceeded();
    }

    [[nodiscard]]
    bool has_deadline() const noexcept {
        return has_deadline_;
    }

    [[nodiscard]]
    Clock::time_point deadline() const noexcept {
        return deadline_;
    }

private:
    const std::atomic_bool& cancelled_;
    bool has_deadline_;
    Clock::time_point deadline_;
};

}
