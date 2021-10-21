# Supaprastintos blokų grandinės kūrimas

## Veikio pricimas
Ši programa simuliuoja supaprastinta blokų grandinę.   
Programa atlikinės šiuos veiksmus:
-	Sugeneruos ~1000 vartotojų ir išsaugos faile ```user_begin.txt```
-	Sugeneruos ~10000 transakcijų ir išsaugos faile ```tx_pool.txt```
-	Atliks blokų kasima: 
    -	Iš transakcijų baseino pasirinkama 100 transakcijų.
    -	Skaičiuojamas bloko hash‘as atitinkantis difficulty.
    -	Transakcijos įvykdomos.
    -	Transakcijos pašalinamos iš transakcijų baseino.
    -	Blokas pridėdamas prie blokų grandinės ir išsaugomas ```blocks/blockN.txt``` , kur ```N``` yra bloko numeris.
-	Pasibaigus transakcijoms vartotoju būsena išsaugoma faile ```user_end.txt```.

## Naudojimas
Programos pateikinės progresą tokiu pavidalu: 
```
Mining Block 12
Block finished
Time: 0.453731s

Mining Block 13
Block finished
Time: 1.14258s

Mining Block 14
Block finished
Time: 1.82131s

Mining Block 15
_
```
Rodoma kuris blokas kasamas ir kiek laiko užtruko kasimas.
##
Jeigu hash'a nepavyko gauti per tau tikra kieki kartu bus apie tai pranešta tokiu pavidalu:
```
Mining Block 13
Block mining timeout

Mining Block 13
_
```
##
Pabaigoje programa pateiks šiuos duomenis: 
```
Mining Block 100
Block finished
Time: 0.0424511s

-------------------------
Time elapsed: 122.273s
Blocks mined: 100
Timeouts: 32
Transaction difference: 0
Balance difference: 0
```
`Time elapsed` - Visų blokų kasimo laikas
`Blocks mined` - kiek blokų iškasta
`Timeouts` - Kiek kartu nepavyko iškasti bloko
`Transaction difference` - Transakcijų kiekio skirtumas
`Balance difference` - Pinigų kiekio skirtumas

## Failai
### Vartotojų failai
Failose `user_begin.txt` ir `user_end.txt` saugojami vartojų duomenis atitinkamai prieš ir po kasimo.  
Struktūra:
```
Name: user1
Public_key: 6C04104818A1323C7482DFE56E8D688F7BB18C31D9900E9E797660CA629EE87D
Balance: 30676
----------------------------------------
Name: user2
Public_key: B47EDB95D33724E40D9D24785094709395DEEEF667626001ECC690009D926600
Balance: 48152
----------------------------------------
Name: user3
Public_key: 5C6B832828CABE3D08B23A0B5305F986187AEC630CA4974B84033CFF6F5F36FC
Balance: 37656
----------------------------------------
```
### Transakcijų failai
Faile `tx_pool.txt` saugojami visos sugeneruotos transakcijos tokiu pavidalu: 
```
id: 6418BB25F16777878F1315426D08278ED906C9342D500D0195F7A9AF72BF4966
sender: 4603384733651D027F682EC14292784A3147DBE3787B40A9C75131D736188F46
receiver: 8332E7D2F80948315CD10267E1B2B0F298F3505FCF270CE1BB0FF2762C804A92
amount: 90
---------------------
id: 343617358A0C302C472B8FD584C7C0AA82E18BAECA9104A1659E70FE285B6D3E
sender: EFD746A03258CBBFE48D0F0A0617E8CC5171D0B941DD9DB860BFB5A5FC0209BF
receiver: 8FC30CBD17BD3FA0604A419BEECA9FE9EA76456FE233C0C956183E8DE14C74E7
amount: 176
---------------------
```
### Blokų failai
Blokai saugojami folder'yje `blocks`, failuose `blockN.txt`, kur `N` yra bloko numeris.
struktūra:
```
hash: 001C47FE0C9E43EE0AFDCE7E3A2E9186A58D534774583BA25CE543B13DB218D1
prev_hash: 0035FF350548A8CB1CA574519A3F44295D54E95355A66164846F3DCB9742C7D5
timestamp: 4148901820
version: 0.1
merkle_root: 7239A5D13C9305BDD0CE921F2FFAC8B3CE5C24AA9ECD5B697BA924E21142EF7E
nonce: 1176796182
difficulty: 2
Number of transaction: 100
------------------
id: F95981C6578D93B4DB80DA62C9839833B1603FFDC8936743B30F0B0A940BC567
sender: 6213E070B75F1720CE1D4914EC54952E8F6C2E334592DC36F14E3FAD430E0117
receiver: 8DFA581B7F834F0CC946AA3D9E901DC4ECF6B80C78318ACAFF5AD479DD4304A2
amount: 318
------------------
id: EDA3E68AF48301E7DD82DEC60AF5F2E12E05C247088065C8AEF1381875200451
sender: 4FF50E17E361F8F028331134490C1CCDCE77F93800A3EB68980339A29F5BD214
receiver: 5DB17EBCE14C03179C666A0050AD6EDFD4D0176A3D9F8DF4607FB14746BC42E6
amount: 305
------------------
```
## Kasimo sparta
Lentelėje pateikta kiekvieno `difficulty` skaičiavimo trukmė

| difficulty | total time | 
| --------- | ---------- | 
| 1         | 0.137878s  |
| 2         | 2.09421s   | 
| 3         | 122.273s   | 
| 4         | 2292.22s   | 

Dėl hash funkcijos savybių su kiekvienu ` difficulty ` lygiu skaičiavimo laikas kyla ekstremaliai laikas 
