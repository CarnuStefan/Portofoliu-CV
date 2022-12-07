//
// Created by crnst on 5/5/2022.
//
#include "Teste.h"
#include "../Domain/Carte.h"
#include "../Repository/Repo.h"
#include "cassert"
#include "cstring"
#include "vector"
#include "../Service/Service.h"
#include "../Repository/RepoFile.h"
#include "../Exceptions and Validators/MyException.h"
#include "../Exceptions and Validators/ValidatorCarte.h"

void testEntity() {
    Carte c1;
    c1.setcod(1);
    c1.settitlu("Carte");
    c1.setautor("autor");
    c1.setgen("exemplu");
    c1.setpret(20.75);
    c1.setstoc(10);
    assert(c1.getcod() == 1);
    assert(strcmp(c1.gettitlu(), "Carte") == 0);
    assert(strcmp(c1.getautor(), "autor") == 0);
    assert(strcmp(c1.getgen(), "exemplu") == 0);
    assert(c1.getpret() == 20.75);
    assert(c1.getstoc() == 10);
    Carte c2(2, "2", "23", "32", 2, 2.1);
    assert(c1 > c2);
    assert(c2 < c1);
    assert(c1 != c2);
    assert(c2 != c1);
    c2 = c1;
    assert(c1 == c2);
}

void testRepo() {
    Carte c1(1, "1", "autor", "21", 1, 1.1);
    Carte c2(2, "2", "autor", "32", 2, 2.1);
    Carte c3(3, "3", "autor", "43", 3, 3.1);
    Carte c4(4, "4", "autor", "54", 4, 4.1);
    Carte c5(5, "5", "autor", "65", 5, 5.1);
    Carte c6(5, "6", "autor", "76", 6, 6.1);
    Repo test;
    test.addItem(c1);
    test.addItem(c2);
    test.addItem(c3);
    test.addItem(c4);
    test.addItem(c5);
    std::vector<Carte> gotall = test.getAll();
    assert(gotall.size() == 5);
    assert(gotall[0].getcod() == c1.getcod());
    assert(gotall[1].getstoc() == c2.getstoc());
    assert(gotall[2].getpret() == c3.getpret());
    assert(strcmp(gotall[3].gettitlu(), c4.gettitlu()) == 0);
    assert(strcmp(gotall[4].getgen(), c5.getgen()) == 0);
    assert(strcmp(gotall[0].getautor(), c1.getautor()) == 0);
    Carte cu(1, "2000", "autornou", "2121", 1, 123.123);
    test.updateItem(1, cu);
    gotall = test.getAll();
    assert(gotall[0] == cu);
    assert(test.getSize() == 5);
    int todel=cu.getcod();
    test.removeItem(todel);
    gotall = test.getAll();
    assert(gotall[0] != cu);
    assert(gotall[0] == c2);
    assert(test.getSize() == 4);
    assert(test.getItem(5) == c5);
    try {
        test.addItem(c6);
    }
    catch (MyException &e) {
        assert(true);
    }
}

void testServ() {
    Repo testrepo;
    Service testserv(testrepo);
    Carte c1(1, "1", "autor", "21", 1, 1.1);
    Carte c2(2, "2", "autor", "32", 2, 2.1);
    Carte c3(3, "3", "autor", "43", 3, 3.1);
    Carte c4(4, "4", "autor", "54", 4, 4.1);
    Carte c5(5, "5", "autor", "65", 5, 5.1);
    Carte c6(5, "6", "autor", "76", 6, 6.1);
    testserv.add(1, "1", "autor", "21", 1, 1.1);
    testserv.add(2, "2", "autor", "32", 2, 2.1);
    testserv.add(3, "3", "autor", "43", 3, 3.1);
    testserv.add(4, "4", "autor", "54", 4, 4.1);
    testserv.add(5, "5", "autor", "65", 5, 5.1);
    assert(testserv.size() == 5);
    Carte cu(1, "2000", "autor", "2121", 1, 123.123);
    testserv.update(1, "2000", "autor", "2121", 1, 123.123);
    testserv.remove(3);
    std::vector<Carte> gotall = testserv.getAll();
    assert(gotall[0] == cu);
    assert(gotall[2] == c4);
    assert(testserv.size() == 4);
    testserv.add(6, "titlu1", "autorunu", "exemplu", 14, 12.3);
    testserv.add(7, "titlu2", "autordoi", "exemplugresit", 14, 12.3);
    testserv.add(8, "titlu3", "autortrei", "exemplu", 14, 12.3);
    testserv.add(9, "titlu4", "autorpatru", "exemplu", 14, 12.3);
    vector<Carte> testgen = testserv.getGen("exemplu");
    for (auto &i: testgen) {
        assert(strcmp(i.getgen(), "exemplu") == 0);
    }
    try {
        testserv.add(5, "6", "autor", "76", 6, 6.1);
    }
    catch (MyException &e) {
        assert(true);
    }
}

void testRepofile() {
    Carte c1(1, "1", "autor", "21", 1, 1.1);
    Carte c2(2, "2", "autor", "32", 2, 2.1);
    Carte c3(3, "3", "au tor", "43", 3, 3.1);
    Carte c4(4, "4", "autor", "54", 4, 4.1);
    Carte c5(5, "5", "autor", "65", 5, 5.1);
    Carte c6(5, "6", "autor", "76", 6, 7.1);
    RepoFile test(R"(C:\Users\crnst\Desktop\OOP\Labs\Lab9-10\Test.txt)");
    test.addItem(c1);
    test.addItem(c2);
    test.addItem(c3);
    test.addItem(c4);
    test.addItem(c5);
    test.save_to_file();
    std::vector<Carte> gotall = test.getAll();
    assert(gotall.size() == 5);
    assert(gotall[0].getcod() == c1.getcod());
    assert(gotall[1].getstoc() == c2.getstoc());
    assert(gotall[2].getpret() == c3.getpret());
    assert(strcmp(gotall[3].gettitlu(), c4.gettitlu()) == 0);
    assert(strcmp(gotall[4].getgen(), c5.getgen()) == 0);
    assert(strcmp(gotall[0].getautor(), c1.getautor()) == 0);
    Carte cu(1, "2000", "autor nou", "2121", 1, 123.123);
    test.updateItem(1, cu);
    gotall = test.getAll();
    assert(gotall[0] == cu);
    assert(test.getSize() == 5);
    int todel= cu.getcod();
    test.removeItem(todel);
    gotall = test.getAll();
    assert(gotall[0] != cu);
    assert(gotall[0] == c2);
    assert(test.getSize() == 4);
    assert(test.getItem(5) == c5);
    try {
        test.addItem(c6);
        todel=200;
        test.removeItem(todel);
    }catch (MyException &e) {
        assert(true);
    }
    try {
        ValidatorCarte testv;
        testv.validate("Titlu","123","gen","ab","cd");
    } catch (MyException &e) {
        assert(true);
    }
    test.clear_file();
}
