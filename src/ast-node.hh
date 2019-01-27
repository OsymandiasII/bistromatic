#pragma once

#include <ostream>

namespace bistro
{
  enum class OpType
    {
        PLUS,
        MINUS,
        TIMES,
        DIVIDE,
        MODULO,
        POWER,
    };
    /**
    ** Abstract class ASTNode.
    **
    ** Represents a node of the AST, which you can print or evaluate.
    **/
    template <typename BigNum, typename Base>
    class ASTNode
    {
    public:

        /// The BigNum class used to represent the numbers.
        using bignum_t = BigNum;

        /// The Base class.
        using base_t = Base;

        /// Shared_ptr to a BigNum.
        using num_t = std::shared_ptr<BigNum>;

        using self_t = ASTNode;
        /// Type of a node in the AST.
        /// Keep in mind you should be able to add/delete those.
        using node_t = std::shared_ptr<ASTNode>;

        virtual ~ASTNode() = default;

        /// Print the tree in infix notation, e.g. "(2+3)".
        virtual std::ostream&
        print_infix(std::ostream& out, const base_t& b) const = 0;

        /// Print the tree in polish notation, e.g. "+ 2 3".
        virtual std::ostream&
        print_pol(std::ostream&, const base_t&) const
        {
            throw "Not implemented";
        }

        /// Print the tree in reverse polish notation, e.g. "2 3 +".
        virtual std::ostream&
        print_rpol(std::ostream&, const base_t&) const
        {
            throw "Not implemented";
        }

        /// Evaluate the tree and return a shared_pointer to the result.
        virtual num_t eval() const = 0;
    };

    template <typename BigNum, typename Base>
    class NumberNode : public ASTNode<BigNum, Base>
    {
        
    public:

        /// The BigNum class used to represent the numbers.
        using bignum_t = typename ASTNode<BigNum, Base>::bignum_t;

        /// The Base class.
        using base_t = typename ASTNode<BigNum, Base>::base_t;

        /// Shared_ptr to a BigNum.
        using num_t = typename ASTNode<BigNum, Base>::num_t;

        using self_t = typename ASTNode<BigNum, Base>::self_t;
        /// Type of a node in the AST.
        /// Keep in mind you should be able to add/delete those.
        using node_t = typename ASTNode<BigNum, Base>::node_t;

        NumberNode(const num_t& num)
            : big_(num)
        {}

        /// Print the tree in infix notation, e.g. "(2+3)".
        std::ostream&
        print_infix(std::ostream& out, const base_t& b) const override
        {
            return big_->print(out, b);
        }

        /// Print the tree in polish notation, e.g. "+ 2 3".
        std::ostream&
        print_pol(std::ostream& out, const base_t& b) const override
        {
            return big_->print(out, b);
        }

        /// Print the tree in reverse polish notation, e.g. "2 3 +".
        std::ostream&
        print_rpol(std::ostream& out, const base_t& b) const override
        {
            return big_->print(out, b);
        }

        /// Evaluate the tree and return a shared_pointer to the result.
        num_t eval() const override
        {
            return big_;
        }

    private:
        num_t big_;
    };

    template <typename BigNum, typename Base>
    class BinOpNode : public ASTNode<BigNum, Base>
    {
    public:

        /// The BigNum class used to represent the numbers.
        using bignum_t = typename ASTNode<BigNum, Base>::bignum_t;

        /// The Base class.
        using base_t = typename ASTNode<BigNum, Base>::base_t;

        /// Shared_ptr to a BigNum.
        using num_t = typename ASTNode<BigNum, Base>::num_t;

        using self_t = typename ASTNode<BigNum, Base>::self_t;
        /// Type of a node in the AST.
        /// Keep in mind you should be able to add/delete those.
        using node_t = typename ASTNode<BigNum, Base>::node_t;

        BinOpNode(const node_t& left, const node_t& right, OpType node)
            : left_(left)
            , right_(right)
            , value_(node)
        {}


        /// Print the tree in infix notation, e.g. "(2+3)".
        std::ostream&
        print_infix(std::ostream& out, const base_t& b) const override
        {
            out << "(";
            left_->print_infix(out, b);
            to_str(value_, out);
            right_->print_infix(out, b);
            out  << ")";
            return out;
        }

        /// Print the tree in polish notation, e.g. "+ 2 3".
        std::ostream&
        print_pol(std::ostream& out, const base_t& b) const override
        {
            to_str(value_, out); 
            out << " " ;
            left_->print_pol(out, b)
            << " ";
            right_->print_infix(out, b);
            return out;
        }

        /// Print the tree in reverse polish notation, e.g. "2 3 +".
        std::ostream&
        print_rpol(std::ostream& out , const base_t& b) const override
        {
            left_->print_pol(out, b);
            out << " ";
            right_->print_infix(out, b);
            out << " " ;
            to_str(value_, out);
            return out;
        }

        /// Evaluate the tree and return a shared_pointer to the result.
        num_t eval() const override
        {
            auto l = left_->eval();
            auto r = right_->eval();
            switch(value_) 
            {
                case  OpType::PLUS : return std::make_shared<BigNum>(*l + *r);
                default: return nullptr;
            }
        }

    private:
        void to_str(enum OpType value, std::ostream& out) const
        {
            switch(value) {
                case OpType::PLUS : out << "+";
                            break;
                case OpType::MINUS : out << "-";
                            break;
                case OpType::TIMES : out << "*";
                            break;
                case OpType::DIVIDE : out << "/";
                            break;
                case OpType::MODULO : out << "%";
                            break;
                case OpType::POWER : out << "^";
                            break;
            }
        }

        node_t left_;
        node_t right_;
        OpType value_;
    };

    template <typename BigNum, typename Base>
    class UnOpNode : public ASTNode<BigNum, Base>
    {
    public:

        /// The BigNum class used to represent the numbers.
        using ignum_t = typename ASTNode<BigNum, Base>::bignum_t;

        /// The Base class.
        using base_t = typename ASTNode<BigNum, Base>::base_t;

        /// Shared_ptr to a BigNum.
        using num_t = typename ASTNode<BigNum, Base>::num_t;

        using self_t = typename ASTNode<BigNum, Base>::self_t;
        /// Type of a node in the AST.
        /// Keep in mind you should be able to add/delete those.
        using node_t = typename ASTNode<BigNum, Base>::node_t;

        UnOpNode(const node_t& left, OpType node)
            : left_(left)
            , value_(node)
        {}


        /// Print the tree in infix notation, e.g. "(2+3)".
        std::ostream&
        print_infix(std::ostream& out, const base_t& b) const override
        {
            to_str(value_, out);
            left_->print_infix(out, b);
            return out;
        }

        /// Print the tree in polish notation, e.g. "+ 2 3".
        std::ostream&
        print_pol(std::ostream& out, const base_t& b) const override
        {
            to_str(value_, out);
            out << " ";
            left_->print_pol(out, b); 
            out << " ";
            return out;
        }
  
        /// Print the tree in reverse polish notation, e.g. "2 3 +".
        std::ostream&
        print_rpol(std::ostream& out, const base_t& b) const override
        {
            left_->print_pol(out, b);
            out << " ";
            to_str(value_, out);
            return out;
        }

        /// Evaluate the tree and return a shared_pointer to the result.
        num_t eval() const override
        {
            auto l = left_->eval();
            switch(value_) 
            {
                case  OpType::PLUS : return l;
                case  OpType::MINUS : return l;
                default: return nullptr;
            }
        }

    private:
        void to_str(enum OpType value, std::ostream& out) const
        {
            switch(value) {
                case OpType::PLUS : out << "+";
                            break;
                case OpType::MINUS : out << "-";
                            break;
                case OpType::TIMES : out << "*";
                            break;
                case OpType::DIVIDE : out << "/";
                            break;
                case OpType::MODULO : out << "%";
                            break;
                case OpType::POWER : out << "^";
                            break;
            }
        }

        node_t left_;
        OpType value_;
    };
}
