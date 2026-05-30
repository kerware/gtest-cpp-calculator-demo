#pragma once

#include "calculator/expression_evaluator.h"
#include "calculator/history_repository.h"

#include <memory>
#include <string>

namespace demo {

class AuditSink {
public:
    virtual ~AuditSink() = default;
    virtual void notifySuccess(const std::string& expression, int result) = 0;
    virtual void notifyFailure(const std::string& expression, const std::string& reason) = 0;
};

class OperationService {
public:
    OperationService(ExpressionEvaluator evaluator,
                     HistoryRepository repository,
                     std::shared_ptr<AuditSink> auditSink);

    int evaluateAndStore(const std::string& expression);

private:
    ExpressionEvaluator evaluator_;
    HistoryRepository repository_;
    std::shared_ptr<AuditSink> auditSink_;
};

} // namespace demo
