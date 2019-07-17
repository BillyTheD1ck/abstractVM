/*
** EPITECH PROJECT, 2019
**
** File description:
**
*/

#include "CPU.hpp"

CPU::CPU()
{
    _memory = Memory();
    _register = Register();
    _commands["push"] = &CPU::push;
    _commands["pop"] = &CPU::pop;
    _commands["clear"] = &CPU::clear;
    _commands["dup"] = &CPU::dup;
    _commands["swap"] = &CPU::swap;
    _commands["dump"] = &CPU::dump;
    _commands["assert"] = &CPU::assert;
    _commands["load"] = &CPU::load;
    _commands["store"] = &CPU::store;
    _commands["print"] = &CPU::print;
    _commands["add"] = &CPU::add;
    _commands["sub"] = &CPU::sub;
    _commands["mul"] = &CPU::mul;
    _commands["div"] = &CPU::div;
    _commands["mod"] = &CPU::mod;
    _commands["exit"] = &CPU::exit;
    _operandTypes["int8"] = INT8;
    _operandTypes["int16"] = INT16;
    _operandTypes["int32"] = INT32;
    _operandTypes["float"] = FLOAT;
    _operandTypes["double"] = DOUBLE;
    _operandTypes["bigdecimal"] = BIGDECIMAL;

}

void CPU::executeInstruction(std::vector<std::string> instruction)
{
    if (instruction.size() == 3) {
        _valueType = instruction.at(1);
        _value = instruction.at(2);
    }
    void (CPU::*f)();
    f = _commands.at(instruction.at(0));
    (*this.*f)();
    _value = nullptr;
    _returnValue = nullptr;
    _valueType = nullptr;
}

void CPU::push()
{
    IOperand *operand = Factory::createOperand(_operandTypes[_valueType], _value);
    _memory.push(operand);
}

void CPU::pop()
{
    if (_memory.getSize() == 0)
        throw Exception("Error : pop on empty stack.");
    _memory.pop();
}

void CPU::clear()
{
    for (unsigned int i = 0; i < _memory.getSize(); i++) {
        _memory.pop();
    }
}

void CPU::dup()
{
    if (_memory.getSize() < 1)
        throw Exception("Error : dub on empty stack.");

    IOperand *operand = _memory.top();

    _memory.push(operand);
}

void CPU::swap()
{
    if (_memory.getSize() < 2)
        throw Exception("Error : swap on stack of size less than 2.");

    IOperand *first = _memory.pop();
    IOperand *second = _memory.pop();

    _memory.push(second);
    _memory.push(first);
}

void CPU::dump()
{
    for (std::stack<IOperand *> tmp = _memory.getStack(); !tmp.empty(); tmp.pop())
        _returnValue += tmp.top()->toString() + "\n";
}

void CPU::assert()
{
    IOperand *checkValue = Factory::createOperand(_operandTypes[_valueType], _value);

    if (checkValue->getType() != _memory.top()->getType())
        throw Exception("Error : assert value type and top stack value type are not equal.");

    if (checkValue->toString() != _memory.top()->toString())
        throw Exception("Error : assert value is not equal to the top value of the stack.");
}

void CPU::load()
{
    if (!_register.getAt((unsigned int)std::atoi(_value.c_str())))
        throw Exception("Error : register " + _value + " is empty.");

    IOperand *operand = Factory::createOperand(_operandTypes[_valueType], _register.getAt((unsigned int)std::atoi(_value.c_str()))->toString());

    _memory.push(operand);
}

void CPU::store()
{
    if (_memory.getSize() == 0)
        throw Exception("Error : store on empty stack.");

    IOperand *operand = Factory::createOperand(_operandTypes[_valueType], _memory.top()->toString());

    _memory.pop();
    _register.pushAt(operand, (unsigned int)std::atoi(_value.c_str()));
}

void CPU::print()
{
}

void CPU::add()
{
}

void CPU::sub()
{
}

void CPU::mul()
{
}

void CPU::div()
{
}

void CPU::mod()
{
}

void CPU::exit()
{
}