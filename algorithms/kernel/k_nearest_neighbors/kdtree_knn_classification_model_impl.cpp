/* file: kdtree_knn_classification_model_impl.cpp */
/*******************************************************************************
* Copyright 2014-2019 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/*
//++
//  Implementation of the class defining the K-Nearest Neighbors (kNN) model
//--
*/

#include "kdtree_knn_classification_model_impl.h"
#include "serialization_utils.h"
#include "daal_strings.h"

using namespace daal::data_management;
using namespace daal::services;

namespace daal
{
namespace algorithms
{
namespace kdtree_knn_classification
{
namespace interface1
{
__DAAL_REGISTER_SERIALIZATION_CLASS(Model, SERIALIZATION_K_NEAREST_NEIGHBOR_MODEL_ID);

Model::Model(size_t nFeatures) : daal::algorithms::classifier::Model(), _impl(new ModelImpl(nFeatures)) {}

Model::~Model()
{
    delete _impl;
}

Model::Model(size_t nFeatures, services::Status &st) : _impl(new ModelImpl(nFeatures))
{
    DAAL_CHECK_COND_ERROR(_impl, st, services::ErrorMemoryAllocationFailed);
}

services::SharedPtr<Model> Model::create(size_t nFeatures, services::Status *stat)
{
    DAAL_DEFAULT_CREATE_IMPL_EX(Model, nFeatures);
}

services::Status Model::serializeImpl(data_management::InputDataArchive  * arch)
{
    daal::algorithms::classifier::Model::serialImpl<data_management::InputDataArchive, false>(arch);
    _impl->serialImpl<data_management::InputDataArchive, false>(arch);

    return services::Status();
}

services::Status Model::deserializeImpl(const data_management::OutputDataArchive * arch)
{
    daal::algorithms::classifier::Model::serialImpl<const data_management::OutputDataArchive, true>(arch);
    _impl->serialImpl<const data_management::OutputDataArchive, true>(arch);

    return services::Status();
}

size_t Model::getNumberOfFeatures() const
{
    return _impl->getNumberOfFeatures();
}

} // namespace interface1

namespace interface2
{
services::Status Parameter::check() const
{
    // Inherited.
    services::Status s = daal::algorithms::classifier::Parameter::check();

    DAAL_CHECK_EX(k >= 1, services::ErrorIncorrectParameter, services::ParameterName, kStr());
    return s;
}
}
} // namespace kdtree_knn_classification
} // namespace algorithms
} // namespace daal
