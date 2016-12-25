#pragma once
#include <functional>
#include <map>

namespace Pyx
{
    namespace Utility
    {
        // Credits RaptorFactor <3
        template <typename Func> class Callbacks
        {
        public:
            using Callback = std::function<Func>;

            Callbacks()
            {
            }

            size_t Register(Callback const& callback)
            {
                auto const cur_id = next_id_++;
                callbacks_[cur_id] = callback;
                return cur_id;
            }

            void Unregister(size_t id)
            {
                auto const num_removed = callbacks_.erase(id);
                (void)num_removed;
            }

            template <typename... Args>
            void Run(Args&&... args) const
            {
                for (auto const& callback : callbacks_)
                {
                    callback.second(std::forward<Args&&>(args)...);
                }
            }

        private:
            size_t next_id_ = size_t{};
            std::map<size_t, Callback> callbacks_;
        };
    }
}