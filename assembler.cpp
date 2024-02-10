#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
#define forn(i, n) for (ll i = 0; i < ll(n); i++)
#define form(i, n) for (ll i = 1; i <= ll(n); i++)
#define cin(a,n) forn(i,n) cin >> a[i]
#define cout(a,n) forn(i,n) cout << a[i] << ' '
#define FastIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define yes "YES"
#define no "NO"
#define yn(b) cout<<(b?yes:no)<<'\n'
#define pb push_back

const int oo = 1000000010;
const int N = 200010;


//This program will be an assmebler to convert MIPS assembly code to machine code in hexadecimal
//The program will take the MIPS assembly code as input and convert it to machine code
//The program will be able to handle the following instructions:
//R-type instruction, I-type instruction, J-type instruction, FR-type instruction
//The program will also be able to handle the following pseudo instructions:
//bge, ble, bgt, blt, move
//in additon to the following floating point instructions: add.s, div.s, mul.s, sub.s, sqrt.s, inv.s

vector<string> v;
vector<string> machine_code;

map<string, int> register_name_to_number;
map<string, string> mnemonic_to_type;

string bin_to_hex(string s) {
    string hex = "";
    for(int i = 0; i < s.size(); i += 4) {
        int x = 0;
        for(int j = 0; j < 4; j++) {
            x = x * 2 + (s[i + j] - '0');
        }
        if(x < 10) hex += (char)(x + '0');
        else hex += (char)(x - 10 + 'A');
    }
    if(hex.length() < 8) {
        string temp = "";
        for(int i = 0; i < 8 - hex.length(); i++) temp += '0';
        temp += hex;
        hex = temp;
    }
    return hex;
}

void fill_register_name_to_number() {
    register_name_to_number["$zero"] = 0;
    register_name_to_number["$at"] = 1;
    register_name_to_number["$v0"] = 2;
    register_name_to_number["$v1"] = 3;
    register_name_to_number["$a0"] = 4;
    register_name_to_number["$a1"] = 5;
    register_name_to_number["$a2"] = 6;
    register_name_to_number["$a3"] = 7;
    register_name_to_number["$t0"] = 8;
    register_name_to_number["$t1"] = 9;
    register_name_to_number["$t2"] = 10;
    register_name_to_number["$t3"] = 11;
    register_name_to_number["$t4"] = 12;
    register_name_to_number["$t5"] = 13;
    register_name_to_number["$t6"] = 14;
    register_name_to_number["$t7"] = 15;
    register_name_to_number["$s0"] = 16;
    register_name_to_number["$s1"] = 17;
    register_name_to_number["$s2"] = 18;
    register_name_to_number["$s3"] = 19;
    register_name_to_number["$s4"] = 20;
    register_name_to_number["$s5"] = 21;
    register_name_to_number["$s6"] = 22;
    register_name_to_number["$s7"] = 23;
    register_name_to_number["$t8"] = 24;
    register_name_to_number["$t9"] = 25;
    register_name_to_number["$k0"] = 26;
    register_name_to_number["$k1"] = 27;
    register_name_to_number["$gp"] = 28;
    register_name_to_number["$sp"] = 29;
    register_name_to_number["$fp"] = 30;
    register_name_to_number["$ra"] = 31;

    //floating point registers

    register_name_to_number["$f0"] = 0;
    register_name_to_number["$f1"] = 1;
    register_name_to_number["$f2"] = 2;
    register_name_to_number["$f3"] = 3;
    register_name_to_number["$f4"] = 4;
    register_name_to_number["$f5"] = 5;
    register_name_to_number["$f6"] = 6;
    register_name_to_number["$f7"] = 7;
    register_name_to_number["$f8"] = 8;
    register_name_to_number["$f9"] = 9;
    register_name_to_number["$f10"] = 10;
    register_name_to_number["$f11"] = 11;
    register_name_to_number["$f12"] = 12;
    register_name_to_number["$f13"] = 13;
    register_name_to_number["$f14"] = 14;
    register_name_to_number["$f15"] = 15;
    register_name_to_number["$f16"] = 16;
    register_name_to_number["$f17"] = 17;
    register_name_to_number["$f18"] = 18;
    register_name_to_number["$f19"] = 19;
    register_name_to_number["$f20"] = 20;
    register_name_to_number["$f21"] = 21;
    register_name_to_number["$f22"] = 22;
    register_name_to_number["$f23"] = 23;
    register_name_to_number["$f24"] = 24;
    register_name_to_number["$f25"] = 25;
    register_name_to_number["$f26"] = 26;
    register_name_to_number["$f27"] = 27;
    register_name_to_number["$f28"] = 28;
    register_name_to_number["$f29"] = 29;
    register_name_to_number["$f30"] = 30;
    register_name_to_number["$f31"] = 31;

}

void fill_mnemoic_to_type() {

    mnemonic_to_type["add.s"] = "F";
    mnemonic_to_type["sub.s"] = "F";
    mnemonic_to_type["div.s"] = "F";
    mnemonic_to_type["inv.s"] = "F";
    mnemonic_to_type["sqr.s"] = "F";
    mnemonic_to_type["mul.s"] = "F";

    mnemonic_to_type["blt"] = "I";
    mnemonic_to_type["bgt"] = "I";
    mnemonic_to_type["bge"] = "I";
    mnemonic_to_type["ble"] = "I";

    mnemonic_to_type["move"] = "R"; //add $1, $2, $0 (move $2 to $1)
    mnemonic_to_type["nop"] = "R"; //add $0, $0, $0

}

string clean(string x) {
    //lowercase everything
    //remove commas

    string y = "";
    for(int i = 0; i < x.size(); i++) {
        if(x[i] == ',') continue;
        else if(x[i] == '$' || x[i] == '.') y += x[i];
        else if(x[i] >= '0' && x[i] <= '9') y += x[i];
        else y += tolower(x[i]);
    }

    return y;
}

string I_TYPE(string s) {
    // mnemomic $rt, $rs, imm

    string mnemonic = "";
    string rt = "";
    string rs = "";
    string imm = "";

    int i = 0;
    for(; i < s.size(); i++) {
        if(s[i] == ' ') break;
        mnemonic += s[i];
    }
    i++;
    for(; i < s.size(); i++) {
        if(s[i] == ' ') break;
        rt += s[i];
    }
    i++;
    for(; i < s.size(); i++) {
        if(s[i] == ' ') break;
        rs += s[i];
    }
    i++;
    for(; i < s.size(); i++) {
        if(s[i] == ' ') break;
        imm += s[i];
    }

    string machine_code = "";

    if(mnemonic == "blt") {
        machine_code += "001000";
    } else if(mnemonic == "bgt") {
        machine_code += "001100";
    } else if(mnemonic == "ble") {
        machine_code += "001101";
    } else if(mnemonic == "bge") {
        machine_code += "001110";
    }

    machine_code += bitset<5>(register_name_to_number[rs]).to_string();

    machine_code += bitset<5>(register_name_to_number[rt]).to_string();

    machine_code += bitset<16>(stoi(imm)).to_string();

    return machine_code;
}

string F_type(string s) {
    //mnemonic $fd, $fs, $ft

    //format opcode fs ft fd fmt funct

    string mnemonic = "";
    string fd = "";
    string fs = "";
    string ft = "";

    int i = 0;
    for(; i < s.size(); i++) {
        if(s[i] == ' ') break;
        mnemonic += s[i];
    }
    i++;
    for(; i < s.size(); i++) {
        if(s[i] == ' ') break;
        fd += s[i];
    }
    i++;
    for(; i < s.size(); i++) {
        if(s[i] == ' ') break;
        fs += s[i];
    }
    i++;
    for(; i < s.size(); i++) {
        if(s[i] == ' ') break;
        ft += s[i];
    }

    string machine_code = "010001";
    string funct = "";
    string fmt = "01010"; //single precision



    if(mnemonic == "add.s") {
        funct += "000000";
    } else if(mnemonic == "sub.s") {
        funct += "000001";
    } else if(mnemonic == "mul.s") {
        funct += "000010";
    } else if(mnemonic == "div.s") {
        funct += "000011";
    } else if(mnemonic == "sqrt.s") {
        funct += "000100";
    } else if(mnemonic == "inv.s") {
        funct += "000101";
    }

    machine_code += bitset<5>(register_name_to_number[fs]).to_string();
    machine_code += bitset<5>(register_name_to_number[ft]).to_string();
    machine_code += bitset<5>(register_name_to_number[fd]).to_string();
    machine_code += fmt;
    machine_code += funct;

    return machine_code;

}

string MOV(string s) {
    //mov $rd, $rs -> add $rd, $rs, $0
    string mnemonic = "";
    string rd = "";
    string rs = "";

    int i = 0;
    for(; i < s.size(); i++) {
        if(s[i] == ' ') break;
        mnemonic += s[i];
    }
    i++;
    for(; i < s.size(); i++) {
        if(s[i] == ' ') break;
        rd += s[i];
    }
    i++;
    for(; i < s.size(); i++) {
        if(s[i] == ' ') break;
        rs += s[i];
    }

    string machine_code = "000000";
    machine_code += bitset<5>(register_name_to_number[rs]).to_string();
    machine_code += bitset<5>(register_name_to_number["$zero"]).to_string();
    machine_code += bitset<5>(register_name_to_number[rd]).to_string();
    machine_code += "00000";
    machine_code += "100000";

    return machine_code;
}

string translate(string s) {
    string machine_code = "";
    if(s == "nop") return "00000000000000000000000000100000"; //add $0 $0 $0

    string mnemonic = "";

    for(int i = 0; i < s.size(); i++) {
        if(s[i] == ' ') break;
        mnemonic += s[i];
    }

    if(mnemonic[0] == 'b') { //branch pseudo instruction
        return I_TYPE(s);
    }

    if(mnemonic[3] == '.') { // floating point instruction
        return F_type(s);
    }

    if(mnemonic == "mov") {
        return MOV(s);
    }



}


void solve() {

    fill_register_name_to_number();
    fill_mnemoic_to_type();

    string x;
    while(getline(cin,x)) {
        v.push_back(clean(x));
    }

    for(auto s: v) {
        machine_code.push_back(translate(s));
    }

    for(auto s: machine_code) {
        cout << bin_to_hex(s) << '\n';
    }


}

int main(void) {
    FastIO;
#ifndef ONLINE_JUDGE
    freopen("input.text.txt", "r", stdin);
    freopen("output.txt.txt","w",stdout);
#endif
    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
