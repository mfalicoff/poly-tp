echo "######################################################"
echo "Test TP4 INF8480 A20"
echo "######################################################"
host -t ns polymtl.ca
host -t a ns1.polymtl.ca
host -t a ns2.polymtl.ca
echo "######################################################"
curl web.polymtl.ca
echo "---------------------------------------------"
curl dossieretudiant.polymtl.ca
echo "######################################################"
nslookup web.polymtl.ca
echo "---------------------------------------------"
nslookup dossieretudiant.polymtl.ca
echo "---------------------------------------------"
nslookup web.polymtl.ca
echo "---------------------------------------------"
nslookup dossieretudiant.polymtl.ca
echo "---------------------------------------------"
nslookup web.polymtl.ca
echo "---------------------------------------------"
nslookup dossieretudiant.polymtl.ca
echo "######################################################"


