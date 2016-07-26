//-------------------------------------------------------------------------------------------------------
// Copyright (C) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.
//-------------------------------------------------------------------------------------------------------

#pragma once

class ServerThreadContext : public ThreadContextInfo
{
public:
    ServerThreadContext(ThreadContextDataIDL * data);
    ~ServerThreadContext();

    virtual HANDLE GetProcessHandle() const override;

    virtual bool IsThreadBound() const override;

    virtual size_t GetScriptStackLimit() const override;

    virtual intptr_t GetThreadStackLimitAddr() const override;

    virtual intptr_t GetSimdTempAreaAddr(uint8 tempIndex) const override;

    virtual intptr_t GetDisableImplicitFlagsAddr() const override;
    virtual intptr_t GetImplicitCallFlagsAddr() const override;
    virtual intptr_t GetBailOutRegisterSaveSpaceAddr() const override;

    virtual intptr_t GetDebuggingFlagsAddr() const override;
    virtual intptr_t GetDebugStepTypeAddr() const override;
    virtual intptr_t GetDebugFrameAddressAddr() const override;
    virtual intptr_t GetDebugScriptIdWhenSetAddr() const override;

    virtual ptrdiff_t GetChakraBaseAddressDifference() const override;
    virtual ptrdiff_t GetCRTBaseAddressDifference() const override;

    virtual Js::PropertyRecord const * GetPropertyRecord(Js::PropertyId propertyId) override;
    virtual PreReservedVirtualAllocWrapper * GetPreReservedVirtualAllocator() override;

    CodeGenAllocators * GetCodeGenAllocators();
    AllocationPolicyManager * GetAllocationPolicyManager();
    CustomHeap::CodePageAllocators * GetCodePageAllocators();

    void AddToPropertyMap(const Js::PropertyRecord * propertyRecord);
private:
    intptr_t GetRuntimeChakraBaseAddress() const;
    intptr_t GetRuntimeCRTBaseAddress() const;

    typedef JsUtil::BaseHashSet<const Js::PropertyRecord *, HeapAllocator, PrimeSizePolicy, const Js::PropertyRecord *,
        DefaultComparer, JsUtil::SimpleHashedEntry, JsUtil::AsymetricResizeLock> PropertyMap;
    PropertyMap * m_propertyMap;

    Js::DelayLoadWinCoreProcessThreads m_delayLoadWinCoreProcessThreads;
    PreReservedVirtualAllocWrapper m_preReservedVirtualAllocator;
    CustomHeap::CodePageAllocators m_codePageAllocators;
    PageAllocator m_pageAlloc;
    AllocationPolicyManager m_policyManager;
    CodeGenAllocators m_codeGenAlloc;

    ThreadContextDataIDL m_threadContextData;

    ThreadContext * m_threadContext;
    intptr_t m_jitChakraBaseAddress;
    intptr_t m_jitCRTBaseAddress;
};
