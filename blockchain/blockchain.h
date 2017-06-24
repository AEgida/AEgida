#pragma once
#include <vector>
#include "block.h"
#include <memory>

class Blockchain
{
	friend Wallet;
public:
	Blockchain();
	void getBlockchain();
	void getNonValidatedTxes();
	bool validateBlockChain();
	size_t size() const { return blockChain.size(); }
	bool addBlock(Block&);
	~Blockchain();
	void customize(size_t numberOfBlocks, secure_vector<byte> address);
	static std::shared_ptr<Blockchain> instance();
	bool validateTxn(const Transaction&, std::vector<std::pair<Output, size_t>>);
	secure_vector<byte> getLastBlockHash();
	uint32_t getBlockchainSize() const;
	std::vector<Block> getBlocksAfter(uint64_t) const;
	int64_t findByHash(secure_vector<byte>);
	void addTx(const Transaction& tx);
	std::vector<uint8_t> 
	getLastBlockData() 
	{ return blockChain.back().getBlockData(); }
private:
	static std::shared_ptr<Blockchain> _self;
	size_t bits = 1;
	bool validateBlock(Block&);
	bool validateMerkleRoot(const Block&);
	bool validateFirstTxn(const Transaction&);
	size_t validateInputs(const Transaction&, std::vector<std::pair<Output, size_t>>);//returns amount of money taken from inputs
	bool validateSignature(const Transaction&);
	bool validateTails(const Transaction&, size_t);
	void restore(std::vector<std::pair<Output, size_t>>);
	void setAvailibleTxes(Block&);
	void clearAvailibleTxes();
	void clearNonValidated(Block);//NEW
	std::vector<Block> blockChain;
	std::vector<Block> nonValidatedBlockChain;
};