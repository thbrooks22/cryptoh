//
// Created by Thomas Brooks on 5/28/23.
//
#include "gtest/gtest.h"
#include "hash/sha/sha256.h"

class SHA256Test : public ::testing::Test {
protected:
    sha256* sha;

    void SetUp() override {
        sha = new sha256();
    }

    void TearDown() override {
        delete sha;
    }
};

TEST_F(SHA256Test, EmptyString){
    sha->consume("");
    EXPECT_EQ(sha->digest(), "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
}

TEST_F(SHA256Test, ShortString){
    sha->consume("Hello, world!");
    EXPECT_EQ(sha->digest(), "315f5bdb76d078c43b8ac0064e4a0164612b1fce77c869345bfc94c75894edd3");
}

// TODO: Look into why this is failing
// Appears always giving same response on len >= 64
// Last correct val is "Quamquam te, Marce fili, annum iam audientem Cratippum " which is len 55
TEST_F(SHA256Test, MediumString){
    sha->consume(
            "Quamquam te, Marce fili, annum iam audientem Cratippum idque Athenis abundare oportet"
    );
    EXPECT_EQ(sha->digest(), "88f7a2b8a5db7a844a56bc2f4a6f55bf33e58ec23ef0127b964537e0a6a73ff2");
}

TEST_F(SHA256Test, LongString){
    sha->consume(
            "Quamquam te, Marce fili, annum iam audientem Cratippum idque Athenis abundare oportet "
            "praeceptis institutisque philosophiae propter summam et doctoris auctoritatem et urbis, quorum "
            "alter te scientia augere potest, altera exemplis, tamen, ut ipse ad meam utilitatem semper cum "
            "Graecis Latina coniunxi neque id in philosophia solum, sed etiam in dicendi exercitatione feci, "
            "idem tibi censeo faciendum, ut par sis in utriusque orationis facultate. Quam quidem ad rem nos, "
            "ut videmur, magnum attulimus adiumentum hominibus nostris, ut non modo Graecarum litterarum rudes, "
            "sed etiam docti aliquantum se arbitrentur adeptos et ad dicendum et ad iudicandum."
    );
    EXPECT_EQ(sha->digest(), "60bb112e589a93278160b2ff2ce1e28f11b4c188257e92c30d4a54aa3e9e2b30");
}

TEST_F(SHA256Test, VeryLongString){
    sha->consume(
            "[1] Quamquam te, Marce fili, annum iam audientem Cratippum idque Athenis abundare oportet praeceptis "
            "institutisque philosophiae propter summam et doctoris auctoritatem et urbis, quorum alter te scientia "
            "augere potest, altera exemplis, tamen, ut ipse ad meam utilitatem semper cum Graecis Latina coniunxi "
            "neque id in philosophia solum, sed etiam in dicendi exercitatione feci, idem tibi censeo faciendum, ut "
            "par sis in utriusque orationis facultate. Quam quidem ad rem nos, ut videmur, magnum attulimus adiumentum "
            "hominibus nostris, ut non modo Graecarum litterarum rudes, sed etiam docti aliquantum se arbitrentur "
            "adeptos et ad dicendum et ad iudicandum.\n"
            "\n"
            "[2] Quam ob rem disces tu quidem a principe huius aetatis philosophorum et disces quam diu voles; tam diu "
            "autem velle debebis, quoad te quantum proficias non paenitebit. Sed tamen nostra legens non multum a "
            "Peripateticis dissidentia, quoniam utrique Socratici et Platonici volumus esse, de rebus ipsis utere tuo "
            "iudicio – nihil enim impedio – orationem autem Latinam efficies profecto legendis nostris pleniorem. Nec "
            "vero hoc arroganter dictum existimari velim. Nam philosophandi scientiam concedens multis, quod est "
            "oratoris proprium, apte, distincte, ornate dicere, quoniam in eo studio aetatem consumpsi, si id mihi "
            "assumo, videor id meo iure quodam modo vindicare.\n"
            "\n"
            "[3] Quam ob rem magnopere te hortor, mi Cicero, ut non solum orationes meas, sed hos etiam de philosophia "
            "libros, qui iam illis fere se aequarunt, studiose legas, – vis enim maior in illis dicendi sed hoc quoque "
            "colendum est aequabile et temperatum orationis genus. Et id quidem nemini video Graecorum adhuc "
            "contigisse, ut idem utroque in genere elaboraret sequereturque et illud forense dicendi et hoc quietum "
            "disputandi genus, nisi forte Demetrius Phalereus in hoc numero haberi potest, disputator subtilis, orator "
            "parum vehemens, dulcis tamen, ut Theophrasti discipulum possis agnoscere. Nos autem quantum in utroque "
            "profecerimus, aliorum sit iudicium, utrumque certe secuti sumus.\n"
            "\n"
            "[4] Equidem et Platonem existimo si genus forense dicendi tractare voluisset, gravissime et copiosissime "
            "potuisse dicere et Demosthenem si illa, quae a Platone didicerat, tenuisset et pronuntiare voluisset, "
            "ornate splendideque facere potuisse; eodemque modo de Aristotele et Isocrate iudico, quorum uterque suo "
            "studio delectatus contempsit alterum. Sed cum statuissem scribere ad te aliquid hoc tempore, multa "
            "posthac, ab eo ordiri maxime volui, quod et aetati tuae esset aptissimum et auctoritati meae. Nam cum "
            "multa sint in philosophia et gravia et utilia accurate copioseque a philosophis disputata, latissime "
            "patere videntur ea quae de officiis tradita ab illis et praecepta sunt. Nulla enim vitae pars neque "
            "publicis neque privatis neque forensibus neque domesticis in rebus, neque si tecum agas quid, neque si "
            "cum altero contrahas, vacare officio potest in eoque et colendo sita vitae est honestas omnis et "
            "neglegendo turpitudo.\n"
            "\n"
            "[5] Atque haec quidem quaestio communis est omnium philosophorum. Quis est enim, qui nullis officii "
            "praeceptis tradendis philosophum se audeat dicere? Sed sunt non nullae disciplinae, quae propositis "
            "bonorum et malorum finibus officium omne pervertant. Nam qui summum bonum sic instituit, ut nihil habeat "
            "cum virtute coniunctum, idque suis commodis, non honestate metitur, hic, si sibi ipse consentiat et non "
            "interdum naturae bonitate vincatur, neque amicitiam colere possit nec iustitiam nec liberalitatem; fortis "
            "vero dolorem summum malum iudicans aut temperans voluptatem summum bonum statuens esse certe nullo modo "
            "potest.\n"
    );
    EXPECT_EQ(sha->digest(), "c1cadf8371a69fd4bf6f8a768ea5a2074b2112ceed9e26dfdf459030cde16e5c");
}