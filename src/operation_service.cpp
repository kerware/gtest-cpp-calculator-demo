#include "calculator/operation_service.h"

#include <exception>

namespace demo {

OperationService::OperationService(ExpressionEvaluator evaluator,
                                   HistoryRepository repository,
                                   std::shared_ptr<AuditSink> auditSink)
    : evaluator_(std::move(evaluator)),
      repository_(std::move(repository)),
      auditSink_(std::move(auditSink)) {}

int OperationService::evaluateAndStore(const std::string& expression) {
    try {
        const int result = evaluator_.evaluate(expression);
        repository_.append(OperationRecord{expression, result});
        if (auditSink_) {
            auditSink_->notifySuccess(expression, result);
        }
        return result;
    } catch (const std::exception& ex) {
        if (auditSink_) {
            auditSink_->notifyFailure(expression, ex.what());
        }
        throw;
    }
}

} // namespace demo
