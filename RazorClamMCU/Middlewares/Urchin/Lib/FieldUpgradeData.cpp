/* 
UrchinTSS

Copyright (c) Microsoft Corporation

All rights reserved. 

MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.  
*/

// Note: This code was derived from the TCG TPM 2.0 Library Specification at
// http://www.trustedcomputinggroup.org/resources/tpm_library_specification

#include    "stdafx.h"

UINT16
TPM2_FieldUpgradeData_Marshal(
    SESSION *sessionTable,
    UINT32 sessionCnt,
    Marshal_Parms *parms,
    BYTE **buffer,
    INT32 *size
)
{
    if((parms == NULL) ||
        (parms->objectCntIn < TPM2_FieldUpgradeData_HdlCntIn) ||
//        (parms->objectCntOut < TPM2_FieldUpgradeData_HdlCntOut) ||
        (parms->parmIn == NULL) ||
        (parms->parmOut == NULL))
    {
        return TPM_RC_FAILURE;
    }
    return Command_Marshal(
        TPM_CC_FieldUpgradeData,
        sessionTable,
        sessionCnt,
        TPM2_FieldUpgradeData_Parameter_Marshal,
        parms,
        buffer,
        size);
}

TPM_RC
TPM2_FieldUpgradeData_Unmarshal(
    SESSION *sessionTable,
    UINT32 sessionCnt,
    Marshal_Parms *parms,
    BYTE **buffer,
    INT32 *size
)
{
    TPM_RC result = TPM_RC_SUCCESS;
//    FieldUpgradeData_In *in = (FieldUpgradeData_In *)parms->parmIn;
//    FieldUpgradeData_Out *out = (FieldUpgradeData_Out *)parms->parmOut;

    if((parms == NULL) ||
        (parms->objectCntIn < TPM2_FieldUpgradeData_HdlCntIn) ||
//        (parms->objectCntOut < TPM2_FieldUpgradeData_HdlCntOut) ||
        (parms->parmIn == NULL) ||
        (parms->parmOut == NULL))
    {
        return TPM_RC_FAILURE;
    }
    if((result = Command_Unmarshal(
        TPM_CC_FieldUpgradeData,
        sessionTable,
        sessionCnt,
        TPM2_FieldUpgradeData_Parameter_Unmarshal,
        parms,
        buffer,
        size)) == TPM_RC_SUCCESS)
    {
    }
    return result;
}

UINT16
TPM2_FieldUpgradeData_Parameter_Marshal(
    Marshal_Parms *parms,
    BYTE **buffer,
    INT32 *size
)
{
    FieldUpgradeData_In *in = (FieldUpgradeData_In *)parms->parmIn;
//    FieldUpgradeData_Out *out = (FieldUpgradeData_Out *)parms->parmOut;
    UINT16 parameterSize = 0;

    // Create the parameter buffer
    parameterSize += TPM2B_MAX_BUFFER_Marshal(&in->fuData, buffer, size);
    if(*size < 0) return TPM_RC_SIZE;

    return parameterSize;
}

TPM_RC
TPM2_FieldUpgradeData_Parameter_Unmarshal(
    Marshal_Parms *parms,
    BYTE **buffer,
    INT32 *size
)
{
//    FieldUpgradeData_In *in = (FieldUpgradeData_In *)parms->parmIn;
    FieldUpgradeData_Out *out = (FieldUpgradeData_Out *)parms->parmOut;
    TPM_RC result = TPM_RC_SUCCESS;

    // Unmarshal the parameters
    result = TPMT_HA_Unmarshal(&out->nextDigest, buffer, size, TRUE);
    if (result != TPM_RC_SUCCESS) return result;
    result = TPMT_HA_Unmarshal(&out->firstDigest, buffer, size, TRUE);
    if (result != TPM_RC_SUCCESS) return result;

    return result;
}
