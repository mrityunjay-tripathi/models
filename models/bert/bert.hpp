/**
 * @file models/bert/bert.hpp
 * @author Mrityunjay Tripathi
 *
 * Definition of the BERT (Bidirectional Encoder Representation for Transformers).
 *
 * mlpack is free software; you may redistribute it and/or modify it under the
 * terms of the 3-clause BSD license.  You should have received a copy of the
 * 3-clause BSD license along with mlpack.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
 */

#ifndef MODELS_BERT_BERT_HPP
#define MODELS_BERT_BERT_HPP

#include <mlpack/prereqs.hpp>
#include <mlpack/methods/ann/ffn.hpp>
#include <mlpack/methods/ann/layer/layer_types.hpp>
#include <mlpack/methods/ann/init_rules/glorot_init.hpp>

namespace mlpack {
namespace ann /** Artificial Neural Network. */ {

/**
 * @tparam OutputLayerType Type of the last layer to be added to BERT model.
 * @tparam InitType Initilization Rule to be used to initialize parameters.
 * @tparam InputDataType Type of the input data (arma::colvec, arma::mat,
 *         arma::sp_mat or arma::cube).
 * @tparam OutputDataType Type of the output data (arma::colvec, arma::mat,
 *         arma::sp_mat or arma::cube).
 */
template <
  typename OutputLayerType = NegativeLogLikelihood<>,
  typename InitializationRuleType = XavierInitialization,
  typename InputDataType = arma::mat,
  typename OutputDataType = arma::mat
>
class BERT
{
 public:
  BERT();

  /**
   * Create the BERT object using the specified parameters.
   *
   * @param srcVocabSize The size of the vocabulary.
   * @param srcSeqLen The source sequence length.
   * @param numEncoderLayers The number of Transformer Encoder layers.
   * @param dModel The dimensionality of the model.
   * @param numHeads The number of attention heads.
   * @param dropout The dropout rate.
   * @param attentionMask The attention mask used to black-out future sequences.
   * @param keyPaddingMask Blacks out specific tokens.
   */
  BERT(const size_t srcVocabSize,
       const size_t srcSeqLen,
       const size_t numEncoderLayers = 12,
       const size_t dModel = 512,
       const size_t numHeads = 8,
       const double dropout = 0.1,
       const InputDataType& attentionMask = InputDataType(),
       const InputDataType& keyPaddingMask = InputDataType());

  /**
   * Load the network from a local directory.
   *
   * @param filepath The location of the stored model.
   */
  void LoadModel(const std::string& filepath);

  /**
   * Save the network locally.
   *
   * @param filepath The location where the model is to be saved.
   */
  void SaveModel(const std::string& filepath);

 private:
  //! Locally-stored size of the vocabulary.
  size_t srcVocabSize;

  //! Locally-stored source sequence length.
  size_t srcSeqLen;

  //! Locally-stored number of Transformer Encoder blocks.
  size_t numEncoderLayers;

  //! Locally-stored dimensionality of the model.
  size_t dModel;

  //! Locally-stored number of attention heads.
  size_t numHeads;

  //! Locally-stored number of hidden units in FFN.
  size_t dimFFN;

  //! Locally-stored dropout rate.
  double dropout;

  //! Locally-stored attention mask.
  InputDataType attentionMask;

  //! Locally-stored key padding mask.
  InputDataType keyPaddingMask;

  //! Locally-stored complete decoder network.
  FFN<OutputLayerType, InitializationRuleType> bert;
}; // class BERT

} // namespace ann
} // namespace mlpack

// Include implementation.
#include "bert_impl.hpp"

#endif
